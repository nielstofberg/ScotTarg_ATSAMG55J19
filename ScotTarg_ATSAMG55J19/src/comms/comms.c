/*
 * comms.c
 *
 * Created: 06/05/2017 17:21:28
 *  Author: NielSt
 */ 

#include "comms.h"

int buffer_pointer = 0;
char rec_buffer[255];

bool get_command_from_buffer(Command *msg);
void clear_buffer(void);
void send_comamand(Command cmd);

/**
* \brief send the raw timings of a good shot
*
* \return void
*/
void send_good_shot(uint16_t mic1_time, uint16_t mic2_time,uint16_t mic3_time,uint16_t mic4_time, uint16_t shotId)
{
	char msg[15];
	msg[0] = '<';
	msg[14] = '>';
	msg[1] = 0;
	msg[2] = mic1_time >> 8;
	msg[3] = mic1_time;
	msg[4] = 0;
	msg[5] = mic2_time >> 8;
	msg[6] = mic2_time;
	msg[7] = 0;
	msg[8] = mic3_time >> 8;
	msg[9] = mic3_time;
	msg[10] = 0;
	msg[11] = mic4_time >> 8;
	msg[12] = mic4_time;
	msg[13] = (char)shotId;

	for (uint32_t a=0; a < ((uint32_t)sizeof(msg)); a++)
	{
		putchar(msg[a]);
		usart_serial_putchar(COMMS_UART, msg[a]);
	}
}

/**
* \brief Send a message to the master informing of a bad/invalid shot
*
* \return void
*/
void send_bad_shot(uint16_t shotId)
{
	char msg[15];
	msg[0] = '<';
	msg[14] = '>';
	msg[3] = 1;
	msg[6] = 1;
	msg[9] = 1;
	msg[12] = 1;
	msg[13] = (char)shotId;

	for (uint32_t a=0; a < ((uint32_t)sizeof(msg)); a++)
	{
		putchar(msg[a]);
		usart_serial_putchar(COMMS_UART, msg[a]);
	}
}

void send_comamand(Command cmd)
{

}

/**
* \brief Send a test message
*
* \return void
*/
void send_test(void)
{
	char msg[4];
	msg[0] = 'T';
	msg[1] = 'e';
	msg[2] = 's';
	msg[3] = 't';

	for (int a=0; a<4; a++)
	{
		usart_serial_putchar(USART_SERIAL, msg[a]);
	}
}

///**
//* \brief Read any available bytes
//*
//* \return void
//*/
//void read_byte(void)
//{
	//bool checkBuff = false;
	//uint8_t buff;
	//while (usart_serial_is_rx_ready(COMMS_UART))
	//{
		//usart_serial_getchar(COMMS_UART, &buff);
		//rec_buffer[buffer_pointer] = buff;
		//buffer_pointer++;
		//checkBuff = true;
	//}
	//if (checkBuff)
	//{
		//Command myMessage;
		//get_command_from_buffer(&myMessage);
	//}
//}

/**
* \brief Event handler for USART_SERIAL
*
* \return void
*/
void byte_received()
{
	uint8_t buff;
	if (usart_serial_is_rx_ready(COMMS_UART))
	{
		usart_serial_getchar(COMMS_UART, &buff);
		rec_buffer[buffer_pointer] = buff;
		buffer_pointer++;
		Command myMessage;
		if (get_command_from_buffer(&myMessage))
		{
			//do something with command
		}
	}
}

/**
* \brief Check if there is a valid message in the buffer. if there is, separate the command and data and place it in a Message struct.
*
* \return True if valid message was read. False if the buffer contains no valid message.
*/
bool get_command_from_buffer(Command *cmd)
{
	int startIndex = 0;
	int endIndex = 0;
	int readIndex = 0;
	int n;

	while (rec_buffer[startIndex] != START_BYTE)
	{
		startIndex++;
		if (startIndex >= buffer_pointer)
		{
			clear_buffer(); // No bytes have been received that are part of a valid message
			return false;
		}
	}
	readIndex = startIndex + 1;
	
	if (readIndex >= buffer_pointer) 
	{
		return false;
	}
	else if (rec_buffer[readIndex] > BUFFER_SIZE) // If the length byte is bigger than the length of the buffer, this cannot be a valid packet clear the buffer and start over.
	{
		clear_buffer();
		return false;
	}
	else if(rec_buffer[readIndex] > (buffer_pointer - startIndex + 1)) //If the length byte is more that what has already been received, return and wait for the rest of the message.
	{
		return false;
	}
	else
	{
		endIndex = startIndex + rec_buffer[readIndex] - 1;
	}
	if (rec_buffer[endIndex] != END_BYTE) //If there is no end byte at the end of the message, this is not a valid command. Clear the buffer and start over. 
	{
		clear_buffer();
		return false;
	}
	// From this point we know that it is a valid command;
	readIndex++;
	cmd->command = rec_buffer[readIndex++];
	for (n = 0; n < endIndex - startIndex - 3; n++)
	{
		cmd->data[n] = rec_buffer[readIndex++];
	}
	cmd->data[n] = EOL;
	return true;
}

void clear_buffer(void)
{
	for (int n = 0; n < buffer_pointer; n++)
	{
		rec_buffer[n] = 0x0;
	}
	buffer_pointer = 0;
}