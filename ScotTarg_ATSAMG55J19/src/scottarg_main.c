/**
 * \file
 *
 * \brief Clock system example 1.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This example shows how to initialize the clock system and blink a LED
 * at a constant 1 Hz frequency.
 *
 * \section files Main files:
 * - clock_example1_sam.c: clock system example application
 * - conf_board.h: board initialization configuration
 * - conf_clock.h: system clock configuration
 *
 * \section deviceinfo Device Info
 * All SAM devices supported by ASF can be used.
 *
 * \section exampledescription Description of the example
 * A delay routine is used to time the interval between each toggling of a LED.
 * The duration of the delay routine is computed from the frequency of the
 * configured system clock source.
 *
 * The main system clock source and prescalers, along with any PLL
 * and/or DFLL configuration, if supported, are defined in conf_clock.h.
 * Changing any of the defines -- #CONFIG_SYSCLK_SOURCE,
 * #CONFIG_SYSCLK_CPU_DIV, etc. -- should not change the frequency of the
 * blinking LED.
 *
 * Refer to the \ref clk_group API documentation for further information on the
 * configuration.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for SAM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 * Support and FAQ: http://www.atmel.com/design-support/
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "asf.h"
#include "scottarg.h"

/**
 * \brief Handler for System Tick interrupt.
 *
 * Process System Tick Event and increments the ul_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	ul_ms_ticks++;
}

void button_press_handler(const uint32_t id, const uint32_t index)
{
	send_test();
	putchar('X');
	if (systemState != INITIALISING)
	{
		startmotor(FORWARD, 200);
	}
}

/**
 * \brief Initialize the clock system and blink a LED at a constant 1 Hz frequency.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void) 
{
	sysclk_init();
	board_init();
	gpio_init();
	configure_tc00();
	configure_tc01();
	configure_console();
	configure_serial();
	pio_enable_button_interrupt();

	int clockSpeed = sysclk_get_cpu_hz();
	bool mic1_flag = false;
	bool mic2_flag = false;
	bool mic3_flag = false;
	bool mic4_flag = false;
	uint16_t mic1_time = 0;
	uint16_t mic2_time = 0;
	uint16_t mic3_time = 0;
	uint16_t mic4_time = 0;
	uint32_t timeout_marker = 0;
	uint32_t shot_space_marker = 0;
	uint32_t led_freq_marker = 0;

	/* Setup SysTick Timer for 1 msec interrupts */
	if (SysTick_Config(clockSpeed / 1000))
	{
		while (1) 
		{  /* Capture error */
		}
	}

	while (1) 
	{
		if ((ul_ms_ticks - led_freq_marker) >= LED_FREQ)
		{
			led_freq_marker = ul_ms_ticks;
			ioport_toggle_pin_level(EXAMPLE_LED_GPIO);
		}

		read_byte();

		if (systemState == WAITING)
		{
			//! Scan pins for action
			mic1_flag = !ioport_get_pin_level(MIC1_PIN);
			mic2_flag = !ioport_get_pin_level(MIC2_PIN);
			mic3_flag = !ioport_get_pin_level(MIC3_PIN);
			mic4_flag = !ioport_get_pin_level(MIC4_PIN);

			if (mic1_flag || mic2_flag || mic3_flag || mic4_flag)
			{
				tc_start(TC1,0);
				int timeCount = 0;
				timeout_marker = ul_ms_ticks;
				systemState = SHOTSTARTED;
				do 
				{
					if (!mic1_flag)
					{
						mic1_flag = !ioport_get_pin_level(MIC1_PIN);
						if (mic1_flag)
						{
							mic1_time = timeCount;
						}
					}
					if (!mic2_flag)
					{
						mic2_flag = !ioport_get_pin_level(MIC2_PIN);
						if (mic2_flag)
						{
							mic2_time = timeCount;
						}
					}
					if (!mic3_flag)
					{
						mic3_flag = !ioport_get_pin_level(MIC3_PIN);
						if (mic3_flag)
						{
							mic3_time = timeCount;
						}
					}
					if (!mic4_flag)
					{
						mic4_flag = !ioport_get_pin_level(MIC4_PIN);
						if (mic4_flag)
						{
							mic4_time = timeCount;
						}
					}
					timeCount = tc_read_cv(TC1,0);

					if ( mic1_flag && mic2_flag && mic3_flag && mic4_flag)
					{
						systemState = SHOTRECORDED;
					}

					if (ul_ms_ticks-timeout_marker > SHOT_TIME_OUT)
					{
						systemState = SHOTSFAILED;
						break;
					}
				} while (systemState == SHOTSTARTED);
				tc_stop(TC1,0);
			}
		}
		else
		{
			if (systemState == SHOTRECORDED || systemState == SHOTSFAILED)
			{
				if (systemState == SHOTRECORDED)
				{
					send_good_shot(mic1_time, mic2_time, mic3_time, mic4_time, 0);
				}
				else
				{
					send_bad_shot(0);
				}

				systemState = SHOTCOMPLETE;
			}
			else if (systemState == SHOTCOMPLETE)
			{
				//!ADvance Paper
				startmotor(FORWARD, 200);
				// Reset
				mic1_flag = false;
				mic2_flag = false;
				mic3_flag = false;
				mic4_flag = false;
				mic1_time = 0;
				mic2_time = 0;
				mic3_time = 0;
				mic4_time = 0;
				systemState = INITIALISING;
				shot_space_marker = ul_ms_ticks;
			}
			else if (systemState == INITIALISING)
			{
				if(ul_ms_ticks - shot_space_marker > SHOT_SPACING)
				{
					systemState = WAITING;
				}
			}
		}
	}
}

