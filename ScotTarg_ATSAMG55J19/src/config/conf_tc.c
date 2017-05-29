/*
 * timer.c
 *
 * Created: 11/02/2017 23:36:29
 *  Author: Niel
 */ 
 #include "asf.h"
 #include "conf_tc.h"

/**
 Description:   Configure Timer 1 Channel 0
				This timer is used to measure the timing between GPIO pin inputs
 Params:	void
 returns:	void
 */
void configure_shot_timer(void)
{
	uint32_t prescaler = SHOT_TIMER_PRESCALE; 

	/* Configure TC10 TC1 channel 0 */
	pmc_enable_periph_clk(SHOT_TIMER_ID);
	  
	//This line sets the prescaler for TC0 by selecting the TIMER_CLOCK cource
	//Also enables  compare Trigger (code ... |TC_CMR_CPCTRG) although I'm not using it
	tc_init(SHOT_TIMER, SHOT_TIMER_CHANNEL, prescaler | TC_CMR_CPCTRG);  
  }

