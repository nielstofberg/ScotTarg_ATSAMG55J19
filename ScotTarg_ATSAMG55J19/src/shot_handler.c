/*
 * shot_handler.c
 *
 * Created: 22/11/2017 20:27:38
 *  Author: Niel
 */ 

#include "shot_handler.h"

uint16_t times[4] = {0, 0, 0, 0};
uint16_t mic1_time = 0;
uint16_t mic2_time = 0;
uint16_t mic3_time = 0;
uint16_t mic4_time = 0;
uint32_t shot_space_marker = 0;
uint8_t mic_flags = 0;
shot_state_t systemState = INITIALISING;

/*
 *	\brief:	First checks 
 */
void do_shot(void)
{
	if (systemState == WAITING)
	{
		if (mic_flags == MIC_FLAGS_ALL)
		{
			//tc_stop(TC0, TC_MIC1_CHANNEL);
			TC_MICS_1->TC_CHANNEL[2].TC_CCR = 0x02;
			TC_MICS_234->TC_CHANNEL[0].TC_CCR = 0x2;
			TC_MICS_234->TC_CHANNEL[1].TC_CCR = 0x2;
			TC_MICS_234->TC_CHANNEL[2].TC_CCR = 0x2;
			disable_mic_timer_interrupts();

			times[1] = tc_read_cv(TC1, 0);
			times[0] = tc_read_cv(TC0, 2);
			times[2] = tc_read_cv(TC1, 1);
			times[3] = tc_read_cv(TC1, 2);
			if (times[0]==0) times[0] = 0xffff;
			if (times[1]==0) times[1] = 0xffff;
			if (times[2]==0) times[2] = 0xffff;
			if (times[3]==0) times[3] = 0xffff;

				
			int16_t max = get_max(times, 4);
			mic1_time = max - times[0];
			mic2_time = max - times[1];
			mic3_time = max - times[2];
			mic4_time = max - times[3];
			systemState = SHOTRECORDED;

		}
	}
	else
	{
		if (systemState == SHOTRECORDED || systemState == SHOTSFAILED)
		{
			if (systemState == SHOTRECORDED)
			{
				last_shot_id++;
				shot_t shotData = { last_shot_id, mic1_time, mic2_time, mic3_time, mic4_time };
				last_shots[shot_pointer] = shotData;
				shot_pointer += 1;
				if (shot_pointer >= SHOT_LIST_LENGTH) shot_pointer = 0;
			}
			else
			{
				//send_bad_shot(0, false);
			}
			systemState = SHOTCOMPLETE;
		}
		else if (systemState == SHOTCOMPLETE)
		{
			//! ADvance Paper
			motor_start(FORWARD, motor_advance);
			// Reset
			mic_flags = 0;
			mic1_time = 0;
			mic2_time = 0;
			mic3_time = 0;
			mic4_time = 0;
			systemState = INITIALISING;
			shot_space_marker = rtc_ms;
		}
		else if (systemState == INITIALISING)
		{
			if (rtc_ms - shot_space_marker > SHOT_SPACING)
			{
				systemState = WAITING;
				pio_get_interrupt_status(MIC_PIO); // This line seems to stop the PIO interrupts from firing imediately after enabling them
				pio_enable_interrupt(MIC_PIO, MIC1_PIN_MASK | MIC2_PIN_MASK | MIC3_PIN_MASK | MIC4_PIN_MASK);	//!< Enable interrupt on button
				enable_mic_timer_interrupts();
			}
		}
	}
}

/*
 *	\brief:	Returns the last recorded shot
 */
shot_t* get_last_shot(void)
{
	if (shot_pointer > 0)
	{
		return &last_shots[shot_pointer-1];
	}
	else if (last_shot_id > 0)
	{
		return &last_shots[SHOT_LIST_LENGTH-1];
	}
	return NULL;
}

/*
 *	\brief:	Returns the shot with the given ID. If the given ID
 *			is not in the last SHOT_LIST_LENGTH shots, it returns NULL.
 */
shot_t* get_shot(uint16_t shot_id)
{
	for (int n = 0; n < SHOT_LIST_LENGTH; n++)
	{
		if(n < last_shot_id )
		{
			if (last_shots[n].shot_id == shot_id)
			{
				return &last_shots[n];
			}
		}
		else
		{
			break;
		}
	}
	return NULL;
}

void mic1_handler(const uint32_t id, const uint32_t index)
{
	TC_MICS_1->TC_CHANNEL[TC_MIC1_CHANNEL].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	//tc_start(TC_MICS_1, TC_MIC1_CHANNEL);
	pio_disable_interrupt(MIC_PIO, MIC1_PIN_MASK);
	mic_flags |= MIC1_FLAG_MASK;
}

void mic2_handler(const uint32_t id, const uint32_t index)
{
	TC_MICS_234->TC_CHANNEL[TC_MIC2_CHANNEL].TC_CCR = 5;
	//tc_start(TC_MICS_234, TC_MIC2_CHANNEL);
	pio_disable_interrupt(MIC_PIO, MIC2_PIN_MASK);
	mic_flags |= MIC2_FLAG_MASK;
}

void mic3_handler(const uint32_t id, const uint32_t index)
{
	TC_MICS_234->TC_CHANNEL[TC_MIC3_CHANNEL].TC_CCR = 5;
	//tc_start(TC_MICS_234, TC_MIC3_CHANNEL);
	pio_disable_interrupt(MIC_PIO, MIC3_PIN_MASK);
	mic_flags |= MIC3_FLAG_MASK;
}

void mic4_handler(const uint32_t id, const uint32_t index)
{
	TC_MICS_234->TC_CHANNEL[TC_MIC4_CHANNEL].TC_CCR = 5;
	//tc_start(TC_MICS_234, TC_MIC4_CHANNEL);
	pio_disable_interrupt(MIC_PIO, MIC4_PIN_MASK);
	mic_flags |= MIC4_FLAG_MASK;
}


void TC2_Handler(void)
{
	TC_MICS_1->TC_CHANNEL[2].TC_CCR = 0x02;
	TC_MICS_234->TC_CHANNEL[0].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[1].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[2].TC_CCR = 0x2;
	tc_get_status(TC_MICS_1, 2);
}

void TC3_Handler(void)
{
	TC_MICS_1->TC_CHANNEL[2].TC_CCR = 0x02;
	TC_MICS_234->TC_CHANNEL[0].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[1].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[2].TC_CCR = 0x2;
	tc_get_status(TC_MICS_234, 0);
}

void TC4_Handler(void)
{
	TC_MICS_1->TC_CHANNEL[2].TC_CCR = 0x02;
	TC_MICS_234->TC_CHANNEL[0].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[1].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[2].TC_CCR = 0x2;
	tc_get_status(TC_MICS_234, 1);
}

void TC5_Handler(void)
{
	TC_MICS_1->TC_CHANNEL[2].TC_CCR = 0x02;
	TC_MICS_234->TC_CHANNEL[0].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[1].TC_CCR = 0x2;
	TC_MICS_234->TC_CHANNEL[2].TC_CCR = 0x2;
	tc_get_status(TC_MICS_234, 2);
}


void enable_mic_timer_interrupts(void)
{
	tc_enable_interrupt(TC_MICS_1, TC_MIC1_CHANNEL, TC_IER_COVFS);
	tc_enable_interrupt(TC_MICS_234, TC_MIC2_CHANNEL, TC_IER_COVFS);
	tc_enable_interrupt(TC_MICS_234, TC_MIC3_CHANNEL, TC_IER_COVFS);
	tc_enable_interrupt(TC_MICS_234, TC_MIC4_CHANNEL, TC_IER_COVFS);
}

void disable_mic_timer_interrupts(void)
{
	tc_disable_interrupt(TC_MICS_1, TC_MIC1_CHANNEL, TC_IDR_COVFS);
	tc_disable_interrupt(TC_MICS_234, TC_MIC2_CHANNEL, TC_IER_COVFS);
	tc_disable_interrupt(TC_MICS_234, TC_MIC3_CHANNEL, TC_IER_COVFS);
	tc_disable_interrupt(TC_MICS_234, TC_MIC4_CHANNEL, TC_IER_COVFS);
}
