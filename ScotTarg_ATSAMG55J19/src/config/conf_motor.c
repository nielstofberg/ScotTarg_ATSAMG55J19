/*
 * conf_motor.c
 *
 * Created: 29/05/2017 15:18:40
 *  Author: nielst
 */ 

 #include "conf_motor.h"
 #include "motor/motor.h"

 void motor_pins_init(void)
 {
 	ioport_set_pin_dir(MOTOR_PIN_1, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_1, IOPORT_MODE_PULLUP);
 	ioport_set_pin_dir(MOTOR_PIN_2, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_2, IOPORT_MODE_PULLUP);
 	ioport_set_pin_dir(MOTOR_PIN_3, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_3, IOPORT_MODE_PULLUP);
 	ioport_set_pin_dir(MOTOR_PIN_4, IOPORT_DIR_OUTPUT);
 	ioport_set_pin_mode(MOTOR_PIN_4, IOPORT_MODE_PULLUP);
 }

  /**
  Description:   Configuration routine for Timer 0 Channel 0 Can be used for timing at some point but nice code example for simple setup of timer counter. 
  Params:	
  
  returns: 
  */
 void motor_timer_init(void)
 {
 	uint32_t freq = MOTOT_TIMER_FREQ;
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
 	NVIC_EnableIRQ((IRQn_Type) TC0_IRQn);
 	tc_enable_interrupt(MOTOR_TIMER, MOTOR_TIMER_CHANNEL, TC_IER_CPCS);

 	// Start the counter.
 	//tc_start(TC0, 0);
 }

 void TC0_Handler(void)
 {
	//motor_timer_handler();
 }

