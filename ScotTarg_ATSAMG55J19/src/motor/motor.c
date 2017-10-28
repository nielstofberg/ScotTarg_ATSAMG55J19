/*
 * motor.c
 *
 * Created: 25/05/2017 22:53:06
 *  Author: Niel
 */ 

#include "motor.h"

int tc00_ms = 0;
uint32_t motorpins[MOTOR_PIN_COUNT] = {MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4};
uint8_t motorpinindex = 0;
uint32_t motorstepcount = 0;
uint32_t motorsteptarget = 0;
motor_dir_t motorstepdir = FORWARD;

void motor_step(void);

void motor_init(void)
{
 	ioport_set_pin_dir(MOTOR_PIN_1, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_1, IOPORT_MODE_PULLUP);
 	ioport_set_pin_dir(MOTOR_PIN_2, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_2, IOPORT_MODE_PULLUP);
 	ioport_set_pin_dir(MOTOR_PIN_3, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_3, IOPORT_MODE_PULLUP);
 	ioport_set_pin_dir(MOTOR_PIN_4, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_4, IOPORT_MODE_PULLUP);


	// Initialise motor timer
	uint32_t freq = MOTOR_TIMER_FREQ;
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	/* Configure TC0 */
	/* Configure PMC */
	pmc_enable_periph_clk(MOTOR_TIMER_ID);

	//! Get the best devisor/prescaler for the selected frequency
	if (!tc_find_mck_divisor(freq, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk)) {
		return;
	}
	 	
	//This line sets the prescaler for TC0 by selecting the TIMER_CLOCK cource
	//Also enables  compare Trigger (code ... |TC_CMR_CPCTRG) although I'm not using it
	tc_init(MOTOR_TIMER, MOTOR_TIMER_CHANNEL, ul_tcclks | TC_CMR_CPCTRG);
	 	
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div)/freq); //Preload the compare registry with the number of counts it will take to to achieve freq

	// Configure and enable interrupt on RC compare
	NVIC_EnableIRQ((IRQn_Type) MOTOR_TIMER_IRQn);
	tc_enable_interrupt(MOTOR_TIMER, MOTOR_TIMER_CHANNEL, TC_IER_CPCS);
 }

/**
Description:    Interrupt handler for Timer 0 Channel 0
Params:	
returns: 
*/
void motor_timer_handler(void)
{
	tc00_ms ++;
	if (tc00_ms >= STEP_TIME)
	{
		tc00_ms = 0;
		motor_step();
	 }
}

void motor_start(motor_dir_t dir, uint32_t steps)
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
	tc_stop(MOTOR_TIMER, 0);
	pio_set_pin_low(motorpins[motorpinindex]);
	motorstepcount = 0;
}

