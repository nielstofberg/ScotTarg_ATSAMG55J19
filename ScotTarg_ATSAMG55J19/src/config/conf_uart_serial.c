/*
 * conf_uart_serial.c
 *
 * Created: 16/02/2017 15:50:18
 *  Author: Niel
 */ 

 #include "conf_uart_serial.h"
 #include <uart_serial.h>
 #include <stdio_serial.h>

 /**
 * \brief Configure UART console.
 */
void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.charlength = CONF_UART_CHAR_LENGTH,
		.paritytype = CONF_UART_PARITY,
		.stopbits = CONF_UART_STOP_BITS,
	};


	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init((Usart *)CONF_UART, &uart_serial_options);
}

void configure_serial(void)
{
	sam_usart_opt_t usart_serial_options = {
		CONF_UART_BAUDRATE,
		CONF_UART_CHAR_LENGTH,
		CONF_UART_PARITY,
		CONF_UART_STOP_BITS,
		US_MR_CHMODE_NORMAL
	};

			/* Configure console UART. */
	sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	usart_init_rs232(USART_SERIAL, &usart_serial_options, sysclk_get_main_hz());
	//stdio_serial_init((Usart *)CONF_UART1, &usart_serial_options);
	usart_enable_tx(USART_SERIAL);
	usart_enable_rx(USART_SERIAL);
}