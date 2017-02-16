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

#define INITIALISING	0
//* Waiting for a shot or another command
#define WAITING			1
#define SHOTSTARTED		2
#define SHOTRECORDED	3
#define SHOTCOMPLETE	4
#define SHOTSFAILED		5

#define LED_FREQ		500
#define SHOT_TIME_OUT			4

uint16_t systemState = INITIALISING;


#endif /* SCOTTARG_H_ */