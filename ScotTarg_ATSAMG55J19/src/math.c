/*
 * math.c
 *
 * Created: 16/11/2017 22:11:58
 *  Author: Niel
 */ 

 #include "math.h"

uint16_t get_max(uint16_t* values, int16_t length)
{
	uint16_t x;
	uint16_t max = values[0];
	for (x=0; x<length; x++)
	{
		if (values[x] > max)
		{
			max = values[x];
		}
	}
	return max;
}
