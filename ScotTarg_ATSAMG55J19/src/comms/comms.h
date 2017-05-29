/*
 * IncFile1.h
 *
 * Created: 06/05/2017 17:20:12
 *  Author: NielSt
 */ 


#ifndef COMMS_H_
#define COMMS_H_

#include "asf.h"

//#ifndef COMMS_UART
//#define COMMS_UART
//#endif

#define BUFFER_SIZE 50
#define START_BYTE	0x3C
#define END_BYTE	0x3E
#define EOL			0x00

typedef struct command_struct
{
	Byte command;
	Byte data[BUFFER_SIZE];
} Command;

void send_good_shot(uint16_t mic1_time, uint16_t mic2_time,uint16_t mic3_time,uint16_t mic4_time, uint16_t shotId);
void send_bad_shot(uint16_t shotId);
void send_test(void);
void read_byte(void);
void byte_received(void);

#endif /* COMMS_H_ */