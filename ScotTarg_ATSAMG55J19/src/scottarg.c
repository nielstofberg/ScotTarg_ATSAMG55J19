/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include "scottarg.h"

int32_t clockSpeed;
void send_test(void);
void initialise_system(void);

/**
	\brief	Main function and entry point of the system
**/
int main (void)
{
	initialise_system();

	uint32_t mic_port_status;

	rtc_ms = 0;
	uint8_t mic_flags = 0;
	uint16_t mic1_time = 0;
	uint16_t mic2_time = 0;
	uint16_t mic3_time = 0;
	uint16_t mic4_time = 0;
	uint32_t timeout_marker = rtc_ms;
	uint32_t shot_space_marker = rtc_ms;
	uint32_t led_freq_marker = rtc_ms;

	cmd_rec_flag = false;
	motor_advance = MOTOR_STEP_SIZE;
	last_shot.shot_id = 0;

	usart_serial_write_packet(IP_UART,(uint8_t*) SOFTWARE_VERSION, sizeof(SOFTWARE_VERSION)-1);
	ioport_set_pin_level(HAPPY_PIN, false);
	while (1)
	{
		if (rtc_ms >= led_freq_marker + LED_FREQ && rtc_ms > 2000) //!< Flash happy led at LED_FREQ rate, but leave it on for the first 2 seconds
		{
			led_freq_marker = rtc_ms;
			ioport_toggle_pin_level(HAPPY_PIN);
		}
		if (cmd_rec_flag)
		{
			command_handler(new_command);
		}
		if (systemState == WAITING)
		{
			mic_port_status = PIOA->PIO_PDSR;	//< PortA's Pin Data Status Register

			//! Scan pins for action
			mic_flags = ((mic_port_status & MIC1_PIN) == 0) ? MIC1_FLAG_MASK: 0;
			mic_flags |= ((mic_port_status & MIC2_PIN) == 0) ? MIC2_FLAG_MASK: 0; 
			mic_flags |= ((mic_port_status & MIC3_PIN) == 0) ? MIC3_FLAG_MASK: 0; 
			mic_flags |= ((mic_port_status & MIC4_PIN) == 0) ? MIC4_FLAG_MASK: 0; 
			
			if (mic_flags)
			{
				tc_start(SHOT_TIMER, SHOT_TIMER_CHANNEL);
				int timeCount = 0;
				timeout_marker = rtc_ms;
				systemState = SHOTSTARTED;

				do
				{
					mic_port_status = PIOA->PIO_PDSR;	//< PortA's Pin Data Status Register
					if (((mic_flags & MIC1_FLAG_MASK) == 0) && ((mic_port_status & MIC1_PIN) == 0))
					{
						mic1_time = timeCount;
						mic_flags |= MIC1_FLAG_MASK;
					}
					if (((mic_flags & MIC2_FLAG_MASK) == 0) && ((mic_port_status & MIC2_PIN) == 0))
					{
						mic2_time = timeCount;
						mic_flags |= MIC2_FLAG_MASK;
					}
					if (((mic_flags & MIC3_FLAG_MASK) == 0) && ((mic_port_status & MIC3_PIN) == 0))
					{
						mic3_time = timeCount;
						mic_flags |= MIC3_FLAG_MASK;
					}
					if (((mic_flags & MIC4_FLAG_MASK) == 0) && ((mic_port_status & MIC4_PIN) == 0))
					{
						mic4_time = timeCount;
						mic_flags |= MIC4_FLAG_MASK;
					}
					timeCount = tc_read_cv(TC1, 0);

					if (mic_flags == MIC_FLAGS_ALL)
					{
						systemState = SHOTRECORDED;
					}

					if (rtc_ms - timeout_marker > SHOT_TIME_OUT)
					{
						systemState = SHOTSFAILED;
						break;
					}
				} while (systemState == SHOTSTARTED);
				tc_stop(SHOT_TIMER, SHOT_TIMER_CHANNEL);
			}
		}
		else
		{
			if (systemState == SHOTRECORDED || systemState == SHOTSFAILED)
			{
				if (systemState == SHOTRECORDED)
				{
					uint16_t shotId = last_shot.shot_id + 1;
					shot_t shotData = { shotId, mic1_time, mic2_time, mic3_time, mic4_time };
					send_good_shot(shotData, false);
					last_shot = shotData;
				}
				else
				{
					send_bad_shot(0, false);
				}
				systemState = SHOTCOMPLETE;
			}
			else if (systemState == SHOTCOMPLETE)
			{
				//! ADvance Paper
				motor_start(FORWARD, motor_advance);
				// Reset
				mic_flags = 0;
				mic1_time = 0;
				mic2_time = 0;
				mic3_time = 0;
				mic4_time = 0;
				systemState = INITIALISING;
				shot_space_marker = rtc_ms;
			}
			else if (systemState == INITIALISING)
			{
				if (rtc_ms - shot_space_marker > SHOT_SPACING)
				{
					systemState = WAITING;
				}
			}
		}
	}
}

/**
	\brief	initialization class. Sets up all peripherals.
**/
void initialise_system()
{
	sysclk_init();
	board_init();
	motor_init();
	shot_timer_init();

	pio_handler_set(BUTTON_PIO, BUTTON_ID, BUTTON_MASK, PIO_IT_FALL_EDGE, button_press_handler);	//!< Set up button interrupt handler
	NVIC_EnableIRQ(PIOA_IRQn);	//!< Enable PIOA Interrupts	
	pio_enable_interrupt(BUTTON_PIO, BUTTON_MASK);	//!< Enable interrupt on button
	
	serial_init();	 
	NVIC_EnableIRQ((IRQn_Type) FLEXCOM6_IRQn); //!< Enable FLEXCOM6_IRQn
	usart_enable_interrupt(IP_UART, US_IER_RXRDY);  //!< enable interrupt on byte received

	clockSpeed = sysclk_get_cpu_hz();
	//!  Setup SysTick Timer for 1 msec interrupts
	if (SysTick_Config(clockSpeed / 1000))
	{
		while (1)
		{
			// Capture error
		}
	}
}
/**
	\brief	Handler for System Tick interrupt.
**/
void SysTick_Handler(void)
{
	rtc_ms++;
}

#define NUM_LEN 10
static int counter=0;
void send_test(void)
{
	const char *strTest = "\r\nTest ";
	char countstring[NUM_LEN];
	int x=0;

	usart_serial_write_packet(IP_UART,(uint8_t*)strTest,7);
	//usart_serial_putchar(IP_UART, counter++);

	itoa(counter++, countstring, NUM_LEN);
	do
	{
		usart_serial_putchar(IP_UART, countstring[x++]);
		if (countstring[x]=='\0')
		{
			break;
		}
	}while (x<NUM_LEN);
}




