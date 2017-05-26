/*
 * motor.h
 *
 * Created: 25/05/2017 22:50:36
 *  Author: Niel
 */ 


#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#include "asf.h"
#include "config/conf_tc.h"
#include "config/conf_gpio.h" 

#define MOTOR_PIN_COUNT	4
#define FORWARD			0
#define BACKWARD		1

//uint32_t motorpins[];// = {MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4};
//uint8_t motorpinindex;// = 0;
//uint32_t motorstepcount;// = 0;
//uint32_t motorsteptarget;// = 0;
//int8_t motorstepdir;// = FORWARD;

//void TC0_Handler(void);
void startmotor(uint16_t dir, uint32_t steps);
void stepmotor(void);
void stopmotor(void);

#endif /* STEPMOTOR_H_ */