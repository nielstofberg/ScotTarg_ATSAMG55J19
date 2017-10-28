/*
 * system_functions.h
 *
 * Created: 28/10/2017 22:00:26
 *  Author: Niel
 */ 


#ifndef SYSTEM_FUNCTIONS_H_
#define SYSTEM_FUNCTIONS_H_

#include "types.h"
#include "comms/comms.h"
#include "motor/motor.h"

uint16_t motor_advance;
shot_t last_shot;

void command_handler(command_t cmd);
void set_paper_advance(uint16_t adv);
void return_paper_advance(void);
void resend_shot(uint16_t id);

#endif /* SYSTEM_FUNCTIONS_H_ */