/*
 * irq_handlers.c
 *
 * Created: 28/10/2017 14:34:41
 *  Author: Niel
 */ 


#include <asf.h>
#include "motor/motor.h"

void button_press_handler(const uint32_t id, const uint32_t index)
{
	motor_start(BACKWARD, MOTOR_STEP_SIZE);
}

/** USART_SERIAL receive interrupt*/
void FLEXCOM6_Handler()
{
	//byte_received();
	uint8_t buff;
	if (usart_serial_is_rx_ready(IP_UART))
	{
		usart_serial_getchar(IP_UART, &buff);
	}
}

/** Motor Timer handler */
void MOTOR_TIMER_Handler(void)
{
  	/* Clear status bit to acknowledge interrupt */
	tc_get_status(MOTOR_TIMER, 0);
	motor_timer_handler();
}