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

char rec_buffer[255];

 void send_good_shot(uint16_t mic1_time, uint16_t mic2_time,uint16_t mic3_time,uint16_t mic4_time, uint16_t shotId);
 void send_bad_shot(uint16_t shotId);
 void send_test(void);
 void read_byte(void);

#endif /* COMMS_H_ */