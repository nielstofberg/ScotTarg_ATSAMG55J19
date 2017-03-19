/*
 * timer.c
 *
 * Created: 11/02/2017 23:36:29
 *  Author: Niel
 */ 
 #include "asf.h"
 #include "conf_tc.h"

 uint32_t counter = 0;

 /**
  Description:   Configuration routine for Timer 0 Channel 0 Can be used for timing at some point but nice code example for simple setup of timer counter. 
  Params:	
  
  returns: 
  */
 void configure_tc00(void)
 {
 	uint32_t freq = TC00_FREQ;
 	uint32_t ul_div;
 	uint32_t ul_tcclks;
 	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	tc00_ms = 0;

 	/* Configure TC0 */
 	/* Configure PMC */
 	pmc_enable_periph_clk(ID_TC0);

 	//! Get the best devisor/prescaler for the selected frequency
 	if (!tc_find_mck_divisor(freq, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk)) {
	 	return;
 	}
 	
 	//This line sets the prescaler for TC0 by selecting the TIMER_CLOCK cource
 	//Also enables  compare Trigger (code ... |TC_CMR_CPCTRG) although I'm not using it
 	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
 	
 	tc_write_rc(TC0, 0, (ul_sysclk / ul_div)/freq); //Preload the compare registry with the number of counts it will take to to achieve freq

 	// Configure and enable interrupt on RC compare
 	NVIC_EnableIRQ((IRQn_Type) TC0_IRQn);
 	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);

 	/* Start the counter. */
 	//tc_start(TC0, 0);
 }

/**
 Description:   Configure Timer 1 Channel 0
				This timer is used to measure the timing between GPIO pin inputs
 Params:	void
 returns:	void
 */
void configure_tc01(void)
{
	uint32_t prescaler = PRESCALE; 

	/* Configure TC10 TC1 channel 0 */
	pmc_enable_periph_clk(ID_TC3);
	  
	//This line sets the prescaler for TC0 by selecting the TIMER_CLOCK cource
	//Also enables  compare Trigger (code ... |TC_CMR_CPCTRG) although I'm not using it
	tc_init(TC1, 0, prescaler | TC_CMR_CPCTRG);  
  }

