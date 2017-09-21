/*
 * gpio.c
 *
 * Created: 25/11/2015 15:09:36
 *  Author: Niel
 */ 
#include "asf.h"
#include "conf_gpio.h"

/**
 Description: Dummy interrupt handler for  pin_edge_handler()
 */
void dh(const uint32_t id, const uint32_t index);

/**
 Description: Set up gpio port with interrupt enabled  
 Params:	pin - PIO_PAxx
 returns:	void
 */
void gpio_init(void)
{
	ioport_set_pin_dir(MIC1_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(MIC2_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(MIC3_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(MIC4_PIN, IOPORT_DIR_INPUT);

	ioport_set_pin_mode(MIC1_PIN, IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(MIC2_PIN, IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(MIC3_PIN, IOPORT_MODE_PULLUP);
	ioport_set_pin_mode(MIC4_PIN, IOPORT_MODE_PULLUP);

	pio_handler_set(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_ID, PIN_PUSHBUTTON_1_MASK, PIO_IT_FALL_EDGE, button_press_handler);

	NVIC_EnableIRQ(PIOA_IRQn);	
}

/**
 Description: Enable all the relevant gpio interrupts
 returns: void
 */
void gpio_enable_interrupts(void)
{
	pio_enable_interrupt(PIOA, MIC1_PIO | MIC2_PIO | MIC3_PIO | MIC4_PIO);
}

/**
 Description: Disables all the relevant gpio interrupts
 returns: void
 */
void gpio_disable_interrupts(void)
{
	pio_disable_interrupt(PIOA, MIC1_PIO | MIC2_PIO | MIC3_PIO | MIC4_PIO);
}

void pio_enable_button_interrupt(void)
{
		pio_enable_interrupt(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK);
}

/**
 Description:	Placeholder event handler for pin_edge_handler.
				Create new function called void pin_edge_handler(const uint32_t id, const uint32_t index) to overwrite this one.
 Params:	id - ID_PIOA or ID_PIOB
			index - PIO_PAxx of the sender
 returns:	void
 */
void pin_edge_handler(const uint32_t id, const uint32_t index)
	 __attribute__ ((weak, alias("dh")));

void dh(const uint32_t id, const uint32_t index)
{
 	if ((id == ID_PIOA) && (index == MIC1_PIO))
	{
		bool pinHigh = ioport_get_pin_level(MIC1_PIN);
		
		ioport_set_pin_level(HAPPY_LED, pinHigh);
	}
}
