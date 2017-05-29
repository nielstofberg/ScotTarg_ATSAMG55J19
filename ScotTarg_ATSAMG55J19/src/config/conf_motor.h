/*
 * pin_alloc.h
 *
 * Created: 29/05/2017 15:12:25
 *  Author: nielst
 */ 


#ifndef CONF_MOTOR_H_
#define CONF_MOTOR_H_

#include "asf.h"

#define MOTOR_PIN_1			EXT1_PIN_13
#define MOTOR_PIN_2			EXT1_PIN_14
#define MOTOR_PIN_3			EXT4_PIN_5
#define MOTOR_PIN_4			EXT4_PIN_9

#define MOTOR_TIMER			TC0
#define MOTOR_TIMER_ID		ID_TC0
#define MOTOR_TIMER_CHANNEL	0
#define MOTOT_TIMER_FREQ	1000
#define MOTOR_TIMER_IRQn	TC0_IRQn

#define STEP_PIN_1 MOTOR_PIN_1

void motor_timer_init(void);
void motor_pins_init(void);

#endif /* CONF_MOTOR_H_ */