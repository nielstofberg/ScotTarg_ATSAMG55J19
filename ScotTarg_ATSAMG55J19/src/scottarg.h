/*
 * scottarg.h
 *
 * Created: 15/02/2017 20:54:58
 *  Author: Niel
 */ 


#ifndef SCOTTARG_H_
#define SCOTTARG_H_

#include "types.h"
#include "comms/comms.h"
#include "motor/motor.h"

#define INITIALISING	0
//! Waiting for a shot or another command
#define WAITING			1
#define SHOTSTARTED		2
#define SHOTRECORDED	3
#define SHOTCOMPLETE	4
#define SHOTSFAILED		5

#define LED_FREQ		500
#define SHOT_TIME_OUT	4
#define SHOT_SPACING	5000

Shot last_shot;

volatile uint32_t ul_ms_ticks = 0;	//! Global ul_ms_ticks in milliseconds since start of application
uint16_t systemState = INITIALISING;
uint16_t motor_advance = MOTOR_STEP_SIZE;

#endif /* SCOTTARG_H_ */