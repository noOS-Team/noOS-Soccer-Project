/************************************************************************/
/* Author: Marc Spieler                                                 */
/* Team: NoOS                                                           */
/* Created: 01.07.18                                                    */
/************************************************************************/

#include "asf.h"
#include "board.h"
#include "conf_board.h"

void board_init(void)
{
	#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
	#endif
	
	ioport_init();
	
	/* Configure LED pins */
	ioport_set_pin_dir(LED_ONBOARD, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_ONBOARD, 0);
	ioport_set_pin_dir(LED_M1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_M1, 0);
	ioport_set_pin_dir(LED_M2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_M2, 0);
	ioport_set_pin_dir(LED_M3, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_M3, 0);
	ioport_set_pin_dir(LED_BAT, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_BAT, 0);
	
	/* Configure pushbutton pins */
	ioport_set_pin_dir(PB_UP, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB_UP, IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE);
	ioport_set_pin_dir(PB_LEFT, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB_LEFT, IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE);
	ioport_set_pin_dir(PB_MID, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB_MID, IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE);
	ioport_set_pin_dir(PB_RIGHT, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB_RIGHT, IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE);
	ioport_set_pin_dir(PB_DOWN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB_DOWN, IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE);
	ioport_set_pin_dir(PB_RETURN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PB_RETURN, IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE);
	
	/* Configure I2C pins */
	ioport_set_pin_mode(I2C0_DATA, IOPORT_MODE_MUX_A);
	ioport_disable_pin(I2C0_DATA);
	ioport_set_pin_mode(I2C0_CLK, IOPORT_MODE_MUX_A);
	ioport_disable_pin(I2C0_CLK);
}
