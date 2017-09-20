/*
 * gpio.h
 *
 * Created: 25/11/2015 14:48:30
 *  Author: Niel
 */ 

#ifndef CONF_GPIO_H_
#define CONF_GPIO_H_

#include "asf.h"

//Pin Allocations
//#define MIC1_PIN    PIO_PA26_IDX //  IOPORT_CREATE_PIN(PIOA, 26)	//Ext1 pin5
//#define MIC2_PIN    PIO_PA25_IDX //  IOPORT_CREATE_PIN(PIOA, 25)	//Ext1 pin6
//#define MIC3_PIN    PIO_PA24_IDX //  IOPORT_CREATE_PIN(PIOA, 24) //Ext1 pin9
//#define MIC4_PIN    PIO_PA29_IDX //  IOPORT_CREATE_PIN(PIOA, 29)	//Ext1 pin10

#define MIC1_PIN    PIO_PA26_IDX
#define MIC2_PIN    PIO_PA25_IDX
#define MIC3_PIN    PIO_PA24_IDX
#define MIC4_PIN    PIO_PA29_IDX

#define MIC1_PIO	PIO_PA26
#define MIC2_PIO	PIO_PA25
#define MIC3_PIO	PIO_PA24
#define MIC4_PIO	PIO_PA29

//! Function Headers
void gpio_init(void);
void gpio_enable_interrupts(void);
void gpio_disable_interrupts(void);
void pio_enable_button_interrupt(void);
void button_press_handler(const uint32_t id, const uint32_t index);
void pin_edge_handler(const uint32_t id, const uint32_t index);

#endif /* GPIO_SETUP_H_ */