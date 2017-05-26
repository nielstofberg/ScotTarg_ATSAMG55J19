/*
 * IncFile1.h
 *
 * Created: 06/05/2017 17:20:12
 *  Author: NielSt
 */ 


#ifndef COMMS_H_
#define COMMS_H_

#include "asf.h"
#include "config/conf_uart_serial.h"

#define BUFFER_SIZE 50
#define START_BYTE	0x3C
#define END_BYTE	0x3E

typedef struct message_struct
{
	Byte command;
	Byte data[BUFFER_SIZE];
} Message;

void send_good_shot(uint16_t mic1_time, uint16_t mic2_time,uint16_t mic3_time,uint16_t mic4_time, uint16_t shotId);
void send_bad_shot(uint16_t shotId);
void send_test(void);
void read_byte(void);
bool get_command_from_buffer(Message *msg);
void clearbuffer(void);

#endif /* COMMS_H_ */