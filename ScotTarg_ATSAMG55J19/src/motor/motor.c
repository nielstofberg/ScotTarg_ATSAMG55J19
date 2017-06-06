/*
 * motor.c
 *
 * Created: 25/05/2017 22:53:06
 *  Author: Niel
 */ 

#include "motor.h"
#include "config/conf_motor.h"


int tc00_ms = 0;
uint32_t motorpins[4] = {MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4};
uint8_t motorpinindex = 0;
uint32_t motorstepcount = 0;
uint32_t motorsteptarget = 0;
int8_t motorstepdir = FORWARD;

 /**
 Description:    Interrupt handler for Timer 0 Channel 0
 Params:	
 
 returns: 
 */
 void motor_timer_handler(void)
 {
	tc00_ms += 1;
	 /* Clear status bit to acknowledge interrupt */
	 tc_get_status(TC0, 0);

	 if (tc00_ms>=2)
	 {
		tc00_ms = 0;
		motor_step();
	 }
 }

void motor_start(uint16_t dir, uint32_t steps)
{
	motorstepdir = dir;
	motorsteptarget = steps;
	tc_start(MOTOR_TIMER, MOTOR_TIMER_CHANNEL);
}

void motor_step(void)
{
	motorstepcount += 1;
	if (motorstepcount > motorsteptarget)
	{
		motor_stop();
	}
	else
	{
		pio_set_pin_low(motorpins[motorpinindex]);
		if (motorstepdir == FORWARD)
		{
			motorpinindex+=1;
			if (motorpinindex == MOTOR_PIN_COUNT)
			{
				motorpinindex = 0;
			}
		}
		else 
		{
			if(motorpinindex == 0)
			{
				motorpinindex = MOTOR_PIN_COUNT-1;
			}
			else
			{
				motorpinindex -=1;
			}
		}
		pio_set_pin_high(motorpins[motorpinindex]);
	}
}

void motor_stop(void)
{
	tc_stop(TC0, 0);
	pio_set_pin_low(motorpins[motorpinindex]);
	motorstepcount = 0;
}

