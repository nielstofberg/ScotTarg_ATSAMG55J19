/*
 * com_handler.c
 *
 * Created: 22/11/2017 23:25:18
 *  Author: Niel
 */ 

#include "com_handler.h"

Usart* COM_USART;
uint8_t buffer_pointer;
uint8_t buffer_head;

/*
 *	\brief:	Call this function when the software starts to initialize all local variables required in the module
 */
void com_handler_init(Usart* usart)
{
	COM_USART = usart;
	buffer_pointer = 0;
	buffer_head = 0;
	com_receive_flag = false;
}

/*
 *	\brief:	Add a new received byte to the receive buffer
 */
void com_add_to_buffer(uint8_t byteToAdd)
{
	com_buffer[buffer_pointer] = byteToAdd;
	buffer_pointer ++;
	if (buffer_pointer >= COM_BUFFER_SIZE)
	{
		buffer_pointer = 0;
	}
}

/*
 *	\brief:	Clear the receive buffer
 */
void com_clear_rec_buffer()
{
	for (int n = 0; n < buffer_pointer; n++)
	{
		com_buffer[n] = 0x0;
	}
	buffer_pointer = 0;
}

/*
 *	\brief:	Analise the receive buffer to find a complete com packet.
 *			When a packet is found the data is placed in com_received, the 
 *			com_receive_flag is set and the receive buffer is cleared.
 */
void com_find_packet()
{
	command_t cmd;
	int startIndex = 0;
	int endIndex = 0;
	int readIndex = 0;
	int n;
	if (com_receive_flag || (buffer_pointer == 0))	//do not find a new packet until the receive flag has been cleared.
	{
		return;
	}
	while (com_buffer[startIndex] != BYTE_START)
	{
		startIndex++;
		if (startIndex >= buffer_pointer)
		{
			com_clear_rec_buffer(); // No bytes have been received that are part of a valid message
			return;
		}
	}
	readIndex = startIndex + 1;

	if (readIndex >= buffer_pointer)
	{
		return;
	}
	else if (com_buffer[readIndex] > COM_BUFFER_SIZE) // If the length byte is bigger than the length of the buffer, this cannot be a valid packet clear the buffer and start over.
	{
		com_clear_rec_buffer();
		return;
	}
	else if (com_buffer[readIndex] > (buffer_pointer - startIndex + 1)) //If the length byte is more that what has already been received, return and wait for the rest of the message.
	{
		return;
	}
	else
	{
		endIndex = startIndex + com_buffer[readIndex] - 1;
	}
	if (buffer_pointer <= endIndex)
	{
		return;
	}
	else if (com_buffer[endIndex] != BYTE_END) //If there is no end byte at the end of the message, this is not a valid command. Clear the buffer and start over.
	{
		com_clear_rec_buffer();
		return;
	}
	// From this point we know that it is a valid command;
	readIndex++;
	cmd.command = com_buffer[readIndex++];
	for (n = 0; n < endIndex - startIndex - 3; n++)
	{
		cmd.data[n] = com_buffer[readIndex++];
	}
	cmd.data[n] = BYTE_EOL;
	cmd.data_count = n;
	cmd.reply = false;
	com_received = cmd;
	com_receive_flag = true;
	com_clear_rec_buffer();
}

/*
 *	\brief: Send a message that will be created from the data in the Command argument
 */
void com_send_command(command_t cmd)
{
	Byte msg[50];
	int counter = 0;
	int dataCtr = 0;
	msg[counter++] = BYTE_START;
	counter++; // We'll get back to the count byte later 
	if (cmd.reply)
	{
		msg[counter++] = (cmd.ack) ? BYTE_ACK : BYTE_NAK;
	}
	msg[counter++] = cmd.command;
	while (dataCtr < cmd.data_count)
	{
		msg[counter++] = cmd.data[dataCtr++];
	}
	msg[counter++] = BYTE_END;
	msg[1] = counter;
	for (int n = 0; n < counter; n++)
	{
		usart_serial_putchar(COM_USART, msg[n]);
	}
}
