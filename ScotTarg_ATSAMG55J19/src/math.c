/*
 * math.c
 *
 * Created: 16/11/2017 22:11:58
 *  Author: Niel
 */ 

 #include "math.h"

 int16_t get_max(int16_t* values, int16_t length)
 {
	 int16_t x;
	 int16_t max = values[0];
	 for (x=0; x<length; x++)
	 {
		 if (values[x] > max)
		 {
			 max = values[x];
		 }
	 }
	 return max;
 }
