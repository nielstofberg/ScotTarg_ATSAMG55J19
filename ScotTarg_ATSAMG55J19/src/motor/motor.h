/*
	\brief	Stepper motor
	This module manages a stepper motor.
	To use this module:
	Define a timer called MOTOR_TIMER 

		
 * 
 *
 * Created: 25/05/2017 22:50:36
 *  Author: Niel
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "asf.h"
typedef enum
{
	FORWARD = 0,
	BACKWARD = 1
}motor_dir_t;

#define MOTOR_PIN_COUNT	4
#define MOTOR_STEP_SIZE 100 //! Number of steps in one mm
#define STEP_TIME		3	//ms between steps.

void motor_init(void);
void motor_start(motor_dir_t dir, uint32_t steps);
void motor_timer_handler(void);
void motor_stop(void);


#endif /* MOTOR_H_ */