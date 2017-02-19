/*
 * timer.h
 *
 * Created: 11/02/2017 23:34:56
 *  Author: Niel
 */ 
 #ifndef CONF_TC_H_
 #define CONF_TC_H_

 /** Frequincy of TC0 interrupts */
 #define TC00_FREQ			1000

 /**
	Prescaler options:
	PRESCALE 0 == Prescale 1/2 (Clock time)
	PRESCALE 1 == Prescale 1/8 (Clock time)
	PRESCALE 2 == Prescale 1/32 (Clock time)
 */
 #define PRESCALE			2

 /** GLOBAL VARIABLES **/
 volatile int tc00_ms;	//! holds the number of times TC0 interrupt has occurred

 void configure_tc00(void);
 void configure_tc01(void);


 #endif //TIMER_H_