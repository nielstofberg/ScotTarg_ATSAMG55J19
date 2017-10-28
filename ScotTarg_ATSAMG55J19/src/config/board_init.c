/*
 * my_board_init.c
 *
 * Created: 22/09/2017 15:25:00
 *  Author: NielSt
 */ 

 #include <asf.h>
 #include <board.h>
 #include <conf_board.h>

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
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	WDT->WDT_MR = WDT_MR_WDDIS;
#endif

	ioport_init();
	ioport_set_pin_dir(HAPPY_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(HAPPY_LED, IOPORT_PIN_LEVEL_HIGH);

	ioport_set_pin_dir(MIC1_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(MIC2_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(MIC3_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(MIC4_PIN, IOPORT_DIR_INPUT);

	ioport_set_pin_mode(MIC1_PIN, IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(MIC2_PIN, IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(MIC3_PIN, IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(MIC4_PIN, IOPORT_MODE_PULLUP);

	ioport_set_pin_peripheral_mode(USART6_RXD_GPIO, USART6_RXD_FLAGS);
	ioport_set_pin_peripheral_mode(USART6_TXD_GPIO, USART6_TXD_FLAGS);

	pio_handler_set(PIN_BUTTON_PIO, PIN_BUTTON_ID, PIN_BUTTON_MASK, PIO_IT_FALL_EDGE, button_press_handler);
	NVIC_EnableIRQ(PIOA_IRQn);
	pio_enable_interrupt(PIN_BUTTON_PIO, PIN_BUTTON_MASK);
}

/**
 Description:   Configure serial port USART_SERIAL
				In this application this serial port is used to send shot information to the client.
 Params:	void
 returns:	void
 */
void configure_serial(void)
{
	static usart_serial_options_t usart_options = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};

	usart_serial_init(USART_SERIAL, &usart_options);

	NVIC_EnableIRQ((IRQn_Type) FLEXCOM6_IRQn);
	usart_enable_interrupt(USART_SERIAL, US_IER_RXRDY);
}

/**
 Description:   Configure Timer 1 Channel 0
				This timer is used to measure the timing between GPIO pin inputs
 Params:	void
 returns:	void
 */
void configure_shot_timer(void)
{
	uint32_t prescaler = SHOT_TIMER_PRESCALE; 

	/* Configure TC10 TC1 channel 0 */
	pmc_enable_periph_clk(SHOT_TIMER_ID);
	  
	//This line sets the prescaler for TC0 by selecting the TIMER_CLOCK cource
	//Also enables  compare Trigger (code ... |TC_CMR_CPCTRG) although I'm not using it
	tc_init(SHOT_TIMER, SHOT_TIMER_CHANNEL, prescaler | TC_CMR_CPCTRG);  
 }


