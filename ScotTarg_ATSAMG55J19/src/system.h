/*
 * system_functions.h
 *
 * Created: 28/10/2017 22:00:26
 *  Author: Niel
 */ 


#ifndef SYSTEM_FUNCTIONS_H_
#define SYSTEM_FUNCTIONS_H_

#include "types.h"
#include "comms/com_handler.h"
#include "shot_handler.h"
#include "motor/motor.h"

#define SW_VERSION			"0.1"
#define SHOT_LIST_LENGTH	50

uint16_t motor_advance;
uint16_t last_shot_id;
shot_t last_shots[SHOT_LIST_LENGTH];
uint8_t shot_pointer;

void command_handler(command_t cmd);
void set_paper_advance(command_t cmd);
void return_paper_advance(void);
void return_shot(command_t cmd);

#endif /* SYSTEM_FUNCTIONS_H_ */