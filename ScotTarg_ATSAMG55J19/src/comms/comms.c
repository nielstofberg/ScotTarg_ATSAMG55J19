/*
 * comms.c
 *
 * Created: 06/05/2017 17:21:28
 *  Author: NielSt
 */ 

 #include "comms.h"

 int bufferIndex = 0;
 char receiveBuffer[255];

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
		usart_serial_putchar(USART_SERIAL, msg[a]);
	}
}

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
		usart_serial_putchar(USART_SERIAL, msg[a]);
	}
}

bool get_command_from_buffer(Message *msg)
{
	int startIndex = 0;
	int readIndex = 0;
	while (receiveBuffer[startIndex] != START_BYTE)
	{
		startIndex++;
		if (startIndex >= bufferIndex)
		{
			return false;
		}
	}
	readIndex = startIndex +1;
	if (readIndex >= bufferIndex || receiveBuffer[readIndex] > (bufferIndex - startIndex) )
	{
		return false;
	}
	else if (receiveBuffer[readIndex+receiveBuffer[readIndex]]-2)
	{
		for (int n = 0; n < bufferIndex; n++)
		{
			receiveBuffer[n] = 0x0;
		}
		bufferIndex = 0;
		return false;
	}
	return false;
}