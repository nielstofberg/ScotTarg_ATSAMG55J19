/*
 * comms.c
 *
 * Created: 06/05/2017 17:21:28
 *  Author: NielSt
 */ 

 #include "comms.h"

int32_t buffer_pointer = 0;

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

void read_byte(void)
{
	char buff;
	if (usart_serial_is_rx_ready(USART_SERIAL))
	{
		usart_serial_getchar(USART_SERIAL, &buff);
		rec_buffer[buffer_pointer] = buff;
		buffer_pointer++;
	}
}