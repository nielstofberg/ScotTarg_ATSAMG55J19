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

	rtc_ms = 0;
	uint32_t led_freq_marker = rtc_ms;
	last_shot_id = 0;
	shot_pointer = 0;
	motor_advance = MOTOR_STEP_SIZE;

	usart_serial_write_packet(IP_UART,(uint8_t*) SOFTWARE_VERSION, sizeof(SOFTWARE_VERSION)-1);
	ioport_set_pin_level(HAPPY_PIN, false);
	enable_mic_timer_interrupts();
	while (1)
	{
		if (rtc_ms >= led_freq_marker + LED_FREQ && rtc_ms > 2000) //!< Flash happy led at LED_FREQ rate, but leave it on for the first 2 seconds
		{
			led_freq_marker = rtc_ms;
			ioport_toggle_pin_level(HAPPY_PIN);
		}
		if (com_receive_flag)
		{
			command_handler(com_received);
		}
		do_shot();
		com_find_packet();
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
	mic_timer_init();

	pio_handler_set(BUTTON_PIO, BUTTON_ID, BUTTON_MASK, PIO_IT_FALL_EDGE, button_press_handler);	//!< Set up button interrupt handler

	pio_handler_set(MIC_PIO, MIC_PIO_ID, MIC1_PIN_MASK, PIO_IT_LOW_LEVEL, mic1_handler);	//!< Set up button interrupt handler
	pio_handler_set(MIC_PIO, MIC_PIO_ID, MIC2_PIN_MASK, PIO_IT_LOW_LEVEL, mic2_handler);	//!< Set up button interrupt handler
	pio_handler_set(MIC_PIO, MIC_PIO_ID, MIC3_PIN_MASK, PIO_IT_LOW_LEVEL, mic3_handler);	//!< Set up button interrupt handler
	pio_handler_set(MIC_PIO, MIC_PIO_ID, MIC4_PIN_MASK, PIO_IT_LOW_LEVEL, mic4_handler);	//!< Set up button interrupt handler

	NVIC_EnableIRQ(PIOA_IRQn);	//!< Enable PIOA Interrupts	
	pio_enable_interrupt(BUTTON_PIO, BUTTON_MASK);	//!< Enable interrupt on button
	//pio_enable_interrupt(MIC_PIO, MIC1_PIN_MASK);	//!< Enable interrupt on button
	//pio_enable_interrupt(MIC_PIO, MIC2_PIN_MASK);	//!< Enable interrupt on button

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
	com_handler_init(IP_UART);
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




