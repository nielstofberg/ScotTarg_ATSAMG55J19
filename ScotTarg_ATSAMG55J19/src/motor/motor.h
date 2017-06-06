/*
 * motor.h
 *
 * Created: 25/05/2017 22:50:36
 *  Author: Niel
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "asf.h"

//#ifndef MOTOR_TIMER
//#define MOTOR_TIMER
//#endif
//
//#ifndef MOTOR_TIMER_CHANNEL
//#define MOTOR_TIMER_CHANNEL 0
//#endif
//
//#ifndef MOTOR_PIN_1
//#define MOTOR_PIN_1
//#endif
//
//#ifndef MOTOR_PIN_2
//#define MOTOR_PIN_2 
//#endif
//
//#ifndef MOTOR_PIN_3
//#define MOTOR_PIN_3 
//#endif
//
//#ifndef MOTOR_PIN_4
//#define MOTOR_PIN_4
//#endif

#define MOTOR_PIN_COUNT	4
#define FORWARD			0
#define BACKWARD		1
#define MOTOR_STEP_SIZE 100 //! Number of steps in one mm

//void TC0_Handler(void);
void motor_start(uint16_t dir, uint32_t steps);
void motor_timer_handler(void);

void motor_step(void);
void motor_stop(void);


#endif /* MOTOR_H_ */