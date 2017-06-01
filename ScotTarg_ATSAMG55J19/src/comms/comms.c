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

/**
* \brief send the raw timings of a good shot
*
* \return void
*/
void send_good_shot(Shot shot_data, bool reply)
{
	Command cmd;
	uint16_t counter = 0;
	cmd.command = (reply) ? CMD_SHOT_RESEND : CMD_SHOT_PACKET;
	cmd.reply = reply;
	cmd.ack = true;

	cmd.data[counter++] = (shot_data.shot_id >> 8) & 0xFF;
	cmd.data[counter++] = shot_data.shot_id & 0xFF;
	cmd.data[counter++] = (shot_data.mic1_time >> 8) & 0xFF;
	cmd.data[counter++] = shot_data.mic1_time & 0xFF;
	cmd.data[counter++] = (shot_data.mic2_time >> 8) & 0xFF;
	cmd.data[counter++] = shot_data.mic2_time & 0xFF;
	cmd.data[counter++] = (shot_data.mic3_time >> 8) & 0xFF;
	cmd.data[counter++] = shot_data.mic3_time & 0xFF;
	cmd.data[counter++] = (shot_data.mic4_time >> 8) & 0xFF;
	cmd.data[counter++] = shot_data.mic4_time & 0xFF;
	cmd.data_count = counter;

	send_command(cmd);
}

/**
* \brief Send a message to the master informing of a bad/invalid shot
*
* \return void
*/
void send_bad_shot(uint16_t shotId, bool reply)
{
	Command cmd;
	uint16_t counter = 0;
	cmd.command = CMD_SHOT_PACKET;
	cmd.reply = reply;
	cmd.ack = true;

	cmd.data[counter++] = shotId & 0xFF;
	cmd.data[counter++] = (shotId >> 8) & 0xFF;
	cmd.data_count = 2;
	send_command(cmd);
}

/**
* \brief Send a message that will be created from the data in the Command argument
*
* \return void
*/
void send_command(Command cmd)
{
	Byte msg[50];
	int counter = 0;
	int dataCtr = 0;
	msg[counter++] = START_BYTE;
	counter++;
	if (cmd.reply)
	{
		msg[counter++] = (cmd.ack) ? ACK : NAK;
	}
	msg[counter++] = cmd.command;
	while (dataCtr < cmd.data_count)
	{
		msg[counter++] = cmd.data[dataCtr++];
	}
	msg[counter++] = END_BYTE;
	msg[1] = counter;
	for (int n = 0; n < counter; n++)
	{
		putchar(msg[n]);
		usart_serial_putchar(COMMS_UART, msg[n]);
	}
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

	for (int a = 0; a < 4; a++)
	{
		usart_serial_putchar(COMMS_UART, msg[a]);
	}
}

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
		if (cmd_rec_flag)
		{
			return;
		}
		rec_buffer[buffer_pointer] = buff;
		buffer_pointer++;
		if (get_command_from_buffer(&new_command))
		{
			//do something with command
			cmd_rec_flag = true;

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
	else if (rec_buffer[readIndex] > (buffer_pointer - startIndex + 1)) //If the length byte is more that what has already been received, return and wait for the rest of the message.
	{
		return false;
	}
	else
	{
		endIndex = startIndex + rec_buffer[readIndex] - 1;
	}
	if (buffer_pointer <= endIndex)
	{
		return false;
	}
	else if (rec_buffer[endIndex] != END_BYTE) //If there is no end byte at the end of the message, this is not a valid command. Clear the buffer and start over. 
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
	cmd->data_count = n;
	cmd->reply = false;
	clear_buffer();
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