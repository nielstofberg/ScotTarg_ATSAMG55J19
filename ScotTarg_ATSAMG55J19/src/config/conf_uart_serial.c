/*
 * conf_uart_serial.c
 *
 * Created: 16/02/2017 15:50:18
 *  Author: Niel
 */ 

#include "conf_uart_serial.h"
#include "comms/comms.h"

 /**
 * \brief Configure UART console.
 */
/**
 Description:   Configure serial port USART_SERIALUART Console.
				used to plug USB coms directly into the Sam G55 Xplained Pro micro USB slot
 Params:	void
 returns:	void
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

void FLEXCOM6_Handler()
{
	byte_received();
}