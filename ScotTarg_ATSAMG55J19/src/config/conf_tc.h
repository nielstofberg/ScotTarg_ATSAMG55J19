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

 /** LED0 blink time, as number of times TC0 will fire before blinking */
 #define BLINK_PERIOD        100


 /** GLOBAL VARIABLES **/
 volatile bool sec_flag;
 volatile int tc00_ms;

 void configure_tc00(void);
 void configure_tc01(void);


 #endif //TIMER_H_