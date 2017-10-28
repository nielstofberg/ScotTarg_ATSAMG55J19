/*
 * main.h
 *
 * Created: 28/10/2017 14:45:13
 *  Author: Niel
 */ 


#ifndef SCOTTARG_H_
#define SCOTTARG_H_

#include <asf.h>
#include "types.h"
#include "system.h"
#include "motor/motor.h"

#define SOFTWARE_VERSION "0.0.2"

#define LED_FREQ		500
#define SHOT_TIME_OUT	4
#define SHOT_SPACING	5000

shot_state_t systemState = INITIALISING;

#endif /* MAIN_H_ */