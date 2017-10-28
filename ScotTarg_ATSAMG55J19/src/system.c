/*
 * system_functions.c
 *
 * Created: 28/10/2017 22:01:03
 *  Author: Niel
 */ 
#include "system.h"

void command_handler(command_t cmd)
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
	command_t cmd;
	cmd.command = CMD_SET_ADVANCE;
	cmd.data[0] = 0x00 | ma;
	cmd.data_count = 1;
	cmd.reply = true;
	cmd.ack = true;
	send_command(cmd);
}

void resend_shot(uint16_t id)
{
	shot_t shot = last_shot;
	shot.shot_id = id;
	send_good_shot(shot, true);
}