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

#define MIC_FLAGS_ALL	0x0f
#define MIC1_FLAG_MASK	(1u << 0)
#define MIC2_FLAG_MASK	(1u << 1)
#define MIC3_FLAG_MASK	(1u << 2)
#define MIC4_FLAG_MASK	(1u << 3)

#define LED_FREQ		500
#define SHOT_TIME_OUT	4
#define SHOT_SPACING	5000

shot_state_t systemState = INITIALISING;

#endif /* MAIN_H_ */