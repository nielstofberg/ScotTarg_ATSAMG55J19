/*
 * shot_handler.h
 *
 * Created: 22/11/2017 20:27:15
 *  Author: Niel
 */ 


#ifndef SHOT_HANDLER_H_
#define SHOT_HANDLER_H_

#include <asf.h>
#include "math.h"
#include "types.h"
#include "system.h"
#include "motor/motor.h"

#define SHOT_SPACING	5000		//Number of Milliseconds after a shot before the next shot will be recorded
#define MIC_FLAGS_ALL	0x0f
#define MIC1_FLAG_MASK	(1u << 0)
#define MIC2_FLAG_MASK	(1u << 1)
#define MIC3_FLAG_MASK	(1u << 2)
#define MIC4_FLAG_MASK	(1u << 3)

typedef enum
{
	INITIALISING = 0,
	WAITING = 1,
	SHOTSTARTED = 2,
	SHOTRECORDED = 3,
	SHOTCOMPLETE = 4,
	SHOTSFAILED = 5
} shot_state_t;


void do_shot(void);
void enable_mic_timer_interrupts(void);
void disable_mic_timer_interrupts(void);



#endif /* SHOT_HANDLER_H_ */