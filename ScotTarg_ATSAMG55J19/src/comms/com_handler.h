/*
 * com_handler.h
 *
 * Created: 22/11/2017 23:24:58
 *  Author: Niel
 */ 


#ifndef COM_HANDLER_H_
#define COM_HANDLER_H_

#include <asf.h>
#include "types.h"

#define COM_BUFFER_SIZE			100
#define BYTE_START				0x3C	// '<'
#define BYTE_END				0x3E	// '<'
#define BYTE_EOL				0xFF
#define BYTE_ACK				0x06
#define BYTE_NAK				0x15

#define CMD_GET_LAST_SHOT		0x20
#define CMD_RESEND_SHOT			0x21
#define CMD_SET_PAPER_ADVANCE	0x22
#define CMD_GET_PAPER_ADVANCE	0x23
#define CMD_GET_FW_VERSION		0x24


uint8_t com_buffer[COM_BUFFER_SIZE];
bool com_receive_flag;
command_t com_received;

void com_handler_init(Usart* usart);
void com_add_to_buffer(uint8_t byteToAdd);
void com_clear_rec_buffer(void);
void com_find_packet(void);
void com_send_command(command_t cmd);

#endif /* COM_HANDLER_H_ */