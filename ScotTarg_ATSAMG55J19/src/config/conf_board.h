/**
 * \file
 *
 * \brief Board configuration.
 *
 * Copyright (c) 2012-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

#include "compiler.h"

#if BOARD == SAMG55_XPLAINED_PRO // If using Demo board
/** Enable Com Port. */
#define CONF_BOARD_USART6

#else  // If Using ScotTarg Board

#define BOARD_FREQ_SLCK_XTAL		(32768U)
#define BOARD_FREQ_SLCK_BYPASS		(32768U)
#define BOARD_FREQ_MAINCK_XTAL		(12000000U)
#define BOARD_FREQ_MAINCK_BYPASS	(12000000U)
#define BOARD_MCK					CHIP_FREQ_CPU_MAX
/*TBD startup time needs to be adjusted according to measurements */
#define BOARD_OSC_STARTUP_US		15625

#define HAPPY_LED					PIO_PA6_IDX

/** Button input pin */
#define PIN_BUTTON_MASK				PIO_PA2
#define PIN_BUTTON_PIO				PIOA
#define PIN_BUTTON_ID				ID_PIOA

/** Mic input pins */
#define MIC1_PIN					PIO_PA26_IDX
#define MIC2_PIN					PIO_PA25_IDX
#define MIC3_PIN					PIO_PA24_IDX
#define MIC4_PIN					PIO_PA29_IDX

/** Stepper motor output pins */
#define MOTOR_PIN_1					PIO_PA9_IDX
#define MOTOR_PIN_2					PIO_PA10_IDX
#define MOTOR_PIN_3					PIO_PA31_IDX
#define MOTOR_PIN_4					PIO_PA14_IDX

/** Timer Counters:
	Prescaler options:
	PRESCALE 0 == Prescale 1/2 (Clock time)
	PRESCALE 1 == Prescale 1/8 (Clock time)
	PRESCALE 2 == Prescale 1/32 (Clock time)
*/
//* Timer counter for stepper motor */
#define MOTOR_TIMER					TC0
#define MOTOR_TIMER_ID				ID_TC0
#define MOTOR_TIMER_CHANNEL			0
#define MOTOT_TIMER_FREQ			200
#define MOTOR_TIMER_IRQn			TC0_IRQn // Use: void TC0_Handler(void); as interrupt handler

//* Timer counter for Shot timing */
#define SHOT_TIMER					TC1
#define SHOT_TIMER_ID				ID_TC3 // Timer 1, Channel 0 = ID3
#define SHOT_TIMER_CHANNEL			0
#define SHOT_TIMER_PRESCALE			2

/** USART6 pin definitions */
#define USART6_RXD_GPIO				IOPORT_CREATE_PIN(PIOB, 11) //PIO_PB11_IDX
#define USART6_RXD_FLAGS			IOPORT_MODE_MUX_B
#define USART6_TXD_GPIO				IOPORT_CREATE_PIN(PIOB, 10) //PIO_PB10_IDX
#define USART6_TXD_FLAGS			IOPORT_MODE_MUX_B
#define USART6_SCK_GPIO				IOPORT_CREATE_PIN(PIOB, 13)
#define USART6_SCK_FLAGS			IOPORT_MODE_MUX_B
#define USART6_CTS_GPIO				IOPORT_CREATE_PIN(PIOB, 14)
#define USART6_CTS_FLAGS			IOPORT_MODE_MUX_B
#define USART6_RTS_GPIO				IOPORT_CREATE_PIN(PIOB, 15)
#define USART6_RTS_FLAGS			IOPORT_MODE_MUX_B


/* A reference setting for USART */
/** USART Interface */
#define USART_SERIAL                USART6
#define USART_SERIAL_BAUDRATE       9600
#define USART_SERIAL_CHAR_LENGTH    US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY         US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT       false

#define COMMS_UART					USART_SERIAL	// This has to be set for the comms module to work.

void button_press_handler(const uint32_t, const uint32_t);
void configure_serial(void);
void configure_shot_timer(void);
void motor_timer_init(void);
void motor_pins_init(void);

#endif

#endif /* CONF_BOARD_H_INCLUDED */
