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