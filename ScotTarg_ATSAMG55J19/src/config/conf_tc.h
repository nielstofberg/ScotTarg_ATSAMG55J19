/*
 * timer.h
 *
 * Created: 11/02/2017 23:34:56
 *  Author: Niel
 */ 
 #ifndef CONF_TC_H_
 #define CONF_TC_H_

 /** Frequincy of TC0 interrupts */

 /**
	Prescaler options:
	PRESCALE 0 == Prescale 1/2 (Clock time)
	PRESCALE 1 == Prescale 1/8 (Clock time)
	PRESCALE 2 == Prescale 1/32 (Clock time)
 */

 #define SHOT_TIMER				TC1
 #define SHOT_TIMER_ID			ID_TC3 // Timer 1, Channel 0 = ID3
 #define SHOT_TIMER_CHANNEL		0
 #define SHOT_TIMER_PRESCALE	2

 void configure_shot_timer(void);


 #endif //TIMER_H_