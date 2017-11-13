/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

/**
 * \brief Set peripheral mode for IOPORT pins.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param port IOPORT port to configure
 * \param masks IOPORT pin masks to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_port_peripheral_mode(port, masks, mode) \
	do {\
		ioport_set_port_mode(port, masks, mode);\
		ioport_disable_port(port, masks);\
	} while (0)

/**
 * \brief Set peripheral mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_pin_peripheral_mode(pin, mode) \
	do {\
		ioport_set_pin_mode(pin, mode);\
		ioport_disable_pin(pin);\
	} while (0)


void board_init(void)
{

//#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	WDT->WDT_MR = WDT_MR_WDDIS;
//#endif

	ioport_init();

	ioport_set_pin_dir(HAPPY_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(HAPPY_PIN, IOPORT_PIN_LEVEL_HIGH);

	ioport_set_pin_mode(BUTTON_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BUTTON_PIN, IOPORT_MODE_PULLUP);

	ioport_set_pin_peripheral_mode(USART6_RXD_GPIO, USART6_RXD_FLAGS);
	ioport_set_pin_peripheral_mode(USART6_TXD_GPIO, USART6_TXD_FLAGS);

}

void serial_init(void)
{
		static usart_serial_options_t usart_options = {
			.baudrate = IP_UART_BAUDRATE,
			.charlength = IP_UART_CHAR_LENGTH,
			.paritytype = IP_UART_PARITY,
			.stopbits = IP_UART_STOP_BIT
		};

		usart_serial_init(IP_UART, &usart_options);
}

/**
 Description:   Configure Timer 1 Channel 0
				This timer is used to measure the timing between GPIO pin inputs
 Params:	void
 returns:	void
 */
void shot_timer_init(void)
{
	uint32_t prescaler = SHOT_TIMER_PRESCALE; 

	/* Configure TC10 TC1 channel 0 */
	pmc_enable_periph_clk(SHOT_TIMER_ID);
	  
	//This line sets the prescaler for TC0 by selecting the TIMER_CLOCK cource
	//Also enables  compare Trigger (code ... |TC_CMR_CPCTRG) although I'm not using it
	tc_init(SHOT_TIMER, SHOT_TIMER_CHANNEL, prescaler);  
 }
