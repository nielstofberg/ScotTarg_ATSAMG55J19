/*
 * IncFile1.h
 *
 * Created: 06/05/2017 17:20:12
 *  Author: NielSt
 */ 


#ifndef COMMS_H_
#define COMMS_H_

#include "asf.h"
#include "types.h"
#include "com_handler.h"

//#ifndef COMMS_UART
//#define COMMS_UART
//#endif

#define START_BYTE	0x3C
#define END_BYTE	0x3E
#define EOL			0xFF
#define ACK			0x06
#define NAK			0x15

#define CMD_SHOT_PACKET 0x20
#define CMD_SHOT_RESEND 0x21
#define CMD_SET_ADVANCE 0x22
#define CMD_GET_ADVANCE 0x23

command_t new_command;
bool cmd_rec_flag;

void send_good_shot(shot_t shot_data, bool reply);
void send_bad_shot(uint16_t shotId, bool reply);
void send_version(void);
void send_command(command_t cmd);
void read_byte(void);
void byte_received(void);

#endif /* COMMS_H_ */