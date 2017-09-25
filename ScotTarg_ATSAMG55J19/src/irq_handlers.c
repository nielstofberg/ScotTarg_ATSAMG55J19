/*
 * irq_handlers.c
 *
 * Created: 22/09/2017 15:35:59
 *  Author: NielSt
 */ 

 #include "comms/comms.h"
 #include "motor/motor.h"

 /** USART_SERIAL receive interrupt*/
 void FLEXCOM6_Handler()
 {
	 byte_received();
 }

 /** Motor Timer handler */
 void TC0_Handler(void)
 {
	motor_timer_handler();
 }
 
