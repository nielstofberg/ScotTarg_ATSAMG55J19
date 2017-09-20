/*
 * scottarg.c
 *
 * Created: 06/05/2017 17:20:12
 * Author: NielSt
 */ 

#include "scottarg.h"

void command_handler(Command cmd);
void set_paper_advance(uint16_t adv);
void return_paper_advance(void);
void resend_shot(uint16_t id);

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
		motor_start(FORWARD, motor_advance);
	}
}

/**
 * \brief Initialize the clock system and blink a LED at a constant 1 Hz frequency.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
bool jimmy;
	sysclk_init();
	board_init();
	
	//gpio_init();
	//motor_pins_init();
	//motor_timer_init();
	//configure_shot_timer();
	//configure_serial();
	//configure_console();
	//pio_enable_button_interrupt();

	

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

	motor_advance = 2 * MOTOR_STEP_SIZE;
	last_shot.shot_id = 0;
	
	//!  Setup SysTick Timer for 1 msec interrupts
	if (SysTick_Config(clockSpeed / 1000))
	{
		while (1)
		{
			// Capture error
		}
	}
	while (1)
	{
		if ((ul_ms_ticks - led_freq_marker) >= LED_FREQ)
		{
			led_freq_marker = ul_ms_ticks;
			ioport_toggle_pin_level(HAPPY_LED);
			jimmy = (EXT1_PIN_6 == PIO_PA25_IDX);
			if (jimmy)
			{
			ioport_toggle_pin_level(HAPPY_LED);
			}
		}
		/*
		if (cmd_rec_flag)
		{
			command_handler(new_command);
		}

		if (systemState == WAITING)
		{
			//! Scan pins for action
			mic1_flag = !ioport_get_pin_level(MIC1_PIN);
			mic2_flag = !ioport_get_pin_level(MIC2_PIN);
			mic3_flag = !ioport_get_pin_level(MIC3_PIN);
			mic4_flag = !ioport_get_pin_level(MIC4_PIN);

			if (mic1_flag || mic2_flag || mic3_flag || mic4_flag)
			{
				tc_start(SHOT_TIMER, SHOT_TIMER_CHANNEL);
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
					timeCount = tc_read_cv(TC1, 0);

					if (mic1_flag && mic2_flag && mic3_flag && mic4_flag)
					{
						systemState = SHOTRECORDED;
					}

					if (ul_ms_ticks - timeout_marker > SHOT_TIME_OUT)
					{
						systemState = SHOTSFAILED;
						break;
					}
				} while (systemState == SHOTSTARTED);
				tc_stop(SHOT_TIMER, SHOT_TIMER_CHANNEL);
			}
		}
		else
		{
			if (systemState == SHOTRECORDED || systemState == SHOTSFAILED)
			{
				if (systemState == SHOTRECORDED)
				{
					uint16_t shotId = last_shot.shot_id + 1;
					Shot shotData = { shotId, mic1_time, mic2_time, mic3_time, mic4_time };
					send_good_shot(shotData, false);
					last_shot = shotData;
				}
				else
				{
					send_bad_shot(0, false);
				}
				systemState = SHOTCOMPLETE;
			}
			else if (systemState == SHOTCOMPLETE)
			{
				//! ADvance Paper
				motor_start(FORWARD, motor_advance);
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
				if (ul_ms_ticks - shot_space_marker > SHOT_SPACING)
				{
					systemState = WAITING;
				}
			}
		}
		*/
	}
}

void command_handler(Command cmd)
{
	uint16_t data;
	switch (cmd.command)
	{
	case CMD_SHOT_RESEND:
		if (cmd.data_count == 2)
		{
			resend_shot((uint16_t)(cmd.data[0] << 8 | cmd.data[1]));
		}
		else
		{
			cmd.reply = true;
			cmd.ack = false;
			send_command(cmd);
		}
		break;
	case CMD_SET_ADVANCE:
		data = cmd.data[0];
		set_paper_advance(data);
		cmd.data_count = 0;
		cmd.reply = true;
		cmd.ack = true;
		send_command(cmd);
		break;

	case CMD_GET_ADVANCE:
		return_paper_advance();
		break;

	default:
		break;
	}
	cmd_rec_flag = false;
}

void set_paper_advance(uint16_t adv)
{
	motor_advance = adv * MOTOR_STEP_SIZE;
}

void return_paper_advance(void)
{
	int ma = motor_advance / MOTOR_STEP_SIZE;
	Command cmd;
	cmd.command = CMD_SET_ADVANCE;
	cmd.data[0] = 0x00 | ma;
	cmd.data_count = 1;
	cmd.reply = true;
	cmd.ack = true;
	send_command(cmd);
}

void resend_shot(uint16_t id)
{
	Shot shot = last_shot;
	shot.shot_id = id;
	send_good_shot(shot, true);
}