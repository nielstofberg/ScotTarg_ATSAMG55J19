/*
 * system_functions.c
 *
 * Created: 28/10/2017 22:01:03
 *  Author: Niel
 */ 
#include "system.h"

/*
 *	\brief:	This function takes a command structure as an argument and executes the command function
 */
void command_handler(command_t cmd)
{
	switch (cmd.command)
	{
		case CMD_GET_LAST_SHOT:		
		case CMD_RESEND_SHOT:
			return_shot(cmd);
			break;

		case CMD_SET_PAPER_ADVANCE:
			set_paper_advance(cmd);
			break;

		case CMD_GET_PAPER_ADVANCE:
			return_paper_advance();
			break;

		default:
		break;
	}
	com_receive_flag = false;
}

void set_paper_advance(command_t cmd)
{
	command_t replyCmd;
	replyCmd.reply=true;
	replyCmd.command = cmd.command;
	if (cmd.data_count == 1)
	{
		replyCmd.ack = true;
		motor_advance = cmd.data[0] * MOTOR_STEP_SIZE;
	}
	else
	{
		replyCmd.ack = false;
	}
	com_send_command(replyCmd);
}

void return_paper_advance(void)
{
	int ma = motor_advance / MOTOR_STEP_SIZE;
	command_t cmd;
	cmd.command = CMD_SET_PAPER_ADVANCE;
	cmd.data[0] = 0x00 | ma;
	cmd.data_count = 1;
	cmd.reply = true;
	cmd.ack = true;
	com_send_command(cmd);
}

void return_shot(command_t cmd)
{	
	shot_t* replyShot = NULL;
	command_t replyCmd;
	replyCmd.reply = true;
	replyCmd.command = cmd.command;
	if (cmd.command == CMD_GET_LAST_SHOT)
	{
		replyShot = get_last_shot();
	}
	else
	{
		if (cmd.data_count == 2)
		{
			uint16_t id = cmd.data[0] << 8 | cmd.data[1];
			replyShot = get_shot(id);
		}
	}
	if (replyShot != NULL)
	{
		//Send replyShot with command ref;
		replyCmd.ack = true;
		replyCmd.data[0] = (uint8_t)(replyShot->shot_id >> 8);
		replyCmd.data[1] = (uint8_t)(replyShot->shot_id & 0x00ff);
		replyCmd.data[2] = (uint8_t)(replyShot->mic1_time >> 8);
		replyCmd.data[3] = (uint8_t)(replyShot->mic1_time & 0x00ff);
		replyCmd.data[4] = (uint8_t)(replyShot->mic2_time >> 8);
		replyCmd.data[5] = (uint8_t)(replyShot->mic2_time & 0x00ff);
		replyCmd.data[6] = (uint8_t)(replyShot->mic3_time >> 8);
		replyCmd.data[7] = (uint8_t)(replyShot->mic3_time & 0x00ff);
		replyCmd.data[8] = (uint8_t)(replyShot->mic4_time >> 8);
		replyCmd.data[9] = (uint8_t)(replyShot->mic4_time & 0x00ff);
		replyCmd.data_count = 10;
	}
	else
	{
		//Send NAK
		replyCmd.ack = false;
	}

	com_send_command(replyCmd);
}