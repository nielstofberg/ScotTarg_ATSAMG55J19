/*
 * scottarg.h
 *
 * Created: 15/02/2017 20:54:58
 *  Author: Niel
 */ 


#ifndef SCOTTARG_H_
#define SCOTTARG_H_

#include "config/conf_tc.h"
#include "config/conf_gpio.h"
#include "config/conf_uart_serial.h"

#define INITIALISING	0
//! Waiting for a shot or another command
#define WAITING			1
#define SHOTSTARTED		2
#define SHOTRECORDED	3
#define SHOTCOMPLETE	4
#define SHOTSFAILED		5

#define EXAMPLE_LED_GPIO    LED0_GPIO
#define LED_FREQ		500
#define SHOT_TIME_OUT	4
#define SHOT_SPACING	5000

#define MOTOR_PIN_COUNT	4
#define FORWARD			0
#define BACKWARD		1

volatile uint32_t ul_ms_ticks = 0;	//! Global ul_ms_ticks in milliseconds since start of application
uint16_t systemState = INITIALISING;

uint32_t motorpins[] = {MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4};
uint8_t motorpinindex = 0;
uint32_t motorstepcount = 0;
uint32_t motorsteptarget = 0;
int8_t motorstepdir = FORWARD;


//! Functions
void startmotor(uint16_t dir, uint32_t steps);
void stepmotor(void);
void stopmotor(void);

#endif /* SCOTTARG_H_ */