/*
 * types.h
 *
 * Created: 01/06/2017 21:11:36
 *  Author: Niel
 */ 


#ifndef TYPES_H_
#define TYPES_H_

#include "asf.h"

typedef struct
{
	Byte command;
	Byte data[50];
	uint16_t data_count;
	bool reply;
	bool ack;
} command_t;

typedef struct
{
	uint16_t shot_id;
	uint16_t mic1_time;
	uint16_t mic2_time;
	uint16_t mic3_time;
	uint16_t mic4_time;
} shot_t;

#endif /* TYPES_H_ */