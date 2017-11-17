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

/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE

//* Timer counter for stepper motor */
#define MOTOR_TIMER					TC0
#define MOTOR_TIMER_ID				ID_TC0
#define MOTOR_TIMER_CHANNEL			0
#define MOTOR_TIMER_FREQ			200
#define MOTOR_TIMER_IRQn			TC0_IRQn // Use: void TC0_Handler(void); as interrupt handler
#define MOTOR_TIMER_Handler			TC0_Handler

//* Timer counter for Shot timing */
#define TC_MICS_1					TC0
#define TC_MICS_234					TC1
#define TC_MIC1_ID					ID_TC2 // Timer 0, Channel 2 = ID2
#define TC_MIC2_ID					ID_TC3 // Timer 1, Channel 0 = ID3
#define TC_MIC3_ID					ID_TC4 // Timer 1, Channel 1 = ID4
#define TC_MIC4_ID					ID_TC5 // Timer 1, Channel 3 = ID5
#define TC_MIC1_CHANNEL				2
#define TC_MIC2_CHANNEL				0
#define TC_MIC3_CHANNEL				1
#define TC_MIC4_CHANNEL				2
#define TC_MIC_PRESCALE				1	// 1 = 8, 2 = 32 
#define TC_MIC1_IRQn				TC2_IRQn // Use: void TC0_Handler(void); as interrupt handler
#define TC_MIC2_IRQn				TC3_IRQn // Use: void TC1_Handler(void); as interrupt handler
#define TC_MIC3_IRQn				TC4_IRQn // Use: void TC1_Handler(void); as interrupt handler
#define TC_MIC4_IRQn				TC5_IRQn // Use: void TC1_Handler(void); as interrupt handler

#ifdef REMOVED
//! [tc_define_ch2]
/* Configure TC0 channel 2 as capture input. */
#define TC_CHANNEL_CAPTURE			2
#define ID_TC_CAPTURE				ID_TC2
#define PIN_TC_CAPTURE				PIN_TC0_TIOA2
#define PIN_TC_CAPTURE_MUX			PIN_TC0_TIOA2_MUX
//! [tc_define_ch2]

//! [tc_define_irq_handler]
/* Use TC2_Handler for TC capture interrupt. */
#define TC_Handler  TC2_Handler
#define TC_IRQn     TC2_IRQn
//! [tc_define_irq_handler]
#endif

volatile uint32_t rtc_ms;	//!< Global rtc_ms in milliseconds since start of application

void serial_init(void);
void mic_timer_init(void);
void button_press_handler(const uint32_t id, const uint32_t index);
void mic1_handler(const uint32_t id, const uint32_t index);
void mic2_handler(const uint32_t id, const uint32_t index);
void mic3_handler(const uint32_t id, const uint32_t index);
void mic4_handler(const uint32_t id, const uint32_t index);

#endif /* CONF_BOARD_H_INCLUDED */
