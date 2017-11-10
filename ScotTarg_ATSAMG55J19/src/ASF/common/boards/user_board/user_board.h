/**
 * \file
 *
 * \brief User board definition template
 *
 */

 /* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>


/**
 * \def CONF_BOARD_KEEP_WATCHDOG_AT_INIT
 * \brief If defined, the watchdog will remain enabled
 *
 * If this symbol is defined, the watchdog is left running with its current
 * configuration. Otherwise, it is disabled during board initialization.
 */
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	#define CONF_BOARD_KEEP_WATCHDOG_AT_INIT
#endif


/** \name Resonator definitions
 *  @{ */
#define BOARD_FREQ_SLCK_XTAL		(32768U)
#define BOARD_FREQ_SLCK_BYPASS		(32768U)
#define BOARD_FREQ_MAINCK_XTAL		0 /* Not Mounted */
#define BOARD_FREQ_MAINCK_BYPASS	0 /* Not Mounted */
#define BOARD_MCK					CHIP_FREQ_CPU_MAX
/*TBD startup time needs to be adjusted according to measurements */
#define BOARD_OSC_STARTUP_US		15625

//* GPIO pin definitions*/
#define HAPPY_PIN					IOPORT_CREATE_PIN(PIOA, 6)

/** Mic input pins */
#define MIC1_PIN					PIO_PA26	//IOPORT_CREATE_PIN(PIOA,26)
#define MIC2_PIN					PIO_PA25	//IOPORT_CREATE_PIN(PIOA,25)
#define MIC3_PIN					PIO_PA24	//IOPORT_CREATE_PIN(PIOA,24)
#define MIC4_PIN					PIO_PA29	//IOPORT_CREATE_PIN(PIOA,29)

/** Stepper motor output pins */
#define MOTOR_PIN_1					IOPORT_CREATE_PIN(PIOA,9) //PIO_PA9_IDX
#define MOTOR_PIN_2					IOPORT_CREATE_PIN(PIOA,10) //PIO_PA10_IDX
#define MOTOR_PIN_3					IOPORT_CREATE_PIN(PIOA,31) //PIO_PA31_IDX
#define MOTOR_PIN_4					IOPORT_CREATE_PIN(PIOA,14) //PIO_PA14_IDX


#define BUTTON_ID					ID_PIOA
#define BUTTON_PIO					PIOA
#define BUTTON_PIN					IOPORT_CREATE_PIN(PIOA, 2)
#define BUTTON_MASK					PIO_PA2

/** USART6 pin definitions */
#define USART6_RXD_GPIO				IOPORT_CREATE_PIN(PIOB, 11)
#define USART6_RXD_FLAGS			IOPORT_MODE_MUX_B
#define USART6_TXD_GPIO				IOPORT_CREATE_PIN(PIOB, 10)
#define USART6_TXD_FLAGS			IOPORT_MODE_MUX_B
#define USART6_SCK_GPIO				IOPORT_CREATE_PIN(PIOB, 13)
#define USART6_SCK_FLAGS			IOPORT_MODE_MUX_B
#define USART6_CTS_GPIO				IOPORT_CREATE_PIN(PIOB, 14)
#define USART6_CTS_FLAGS			IOPORT_MODE_MUX_B
#define USART6_RTS_GPIO				IOPORT_CREATE_PIN(PIOB, 15)
#define USART6_RTS_FLAGS			IOPORT_MODE_MUX_B
/** @} */


// External oscillator settings.
// Uncomment and set correct values if external oscillator is used.

// External oscillator frequency
//#define BOARD_XOSC_HZ          8000000

// External oscillator type.
//!< External clock signal
//#define BOARD_XOSC_TYPE        XOSC_TYPE_EXTERNAL
//!< 32.768 kHz resonator on TOSC
//#define BOARD_XOSC_TYPE        XOSC_TYPE_32KHZ
//!< 0.4 to 16 MHz resonator on XTALS
//#define BOARD_XOSC_TYPE        XOSC_TYPE_XTAL

// External oscillator startup time
//#define BOARD_XOSC_STARTUP_US  500000


#endif // USER_BOARD_H
