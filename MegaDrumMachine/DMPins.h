#pragma once
#ifndef __DrumMachinePins__
	#define __DrumMachinePins__


/**
 * Control Layout
 *	+----------+
 *  |          |
 *  |  RE  BR  |  
 *  |          |
 *  |  MT  BA  |  
 *  |          |
 *  |  BC  BB  |
 *  |          |
 *	+----------+
 * 
 *  LEGEND
 *	RE = Rotary Encoder
 *  MT = Mode Toggle
 *  BA = Button A
 *  BB = Button B
 *  BC = Button C
 *	BR = Button R
 */


/**
 * Rotary Encoder
 */
#define PIN_ROTARY_CLICK		22
#define PIN_ROTARY_A			20
#define PIN_ROTARY_B			21

/**
 * Mode Toggle Switch
 * PLAY = Play
 * PKIT	= Kit
 * No Connection = Program
 */
#define PIN_MODETOG_A			24
#define PIN_MODETOG_B			25

/**
 * PushButtons
 * BTNA		Metronome On/Off
 * BTNB
 * BTNRED	Play/Stop
 */

#define PIN_BTN_C
#define PIN_BTN_RED		
#define PIN_BTN_B
#define PIN_BTN_A


/**
 * WavTrigger
 */
#define __WT_USE_SERIAL1__

/**
 *  Button Reader
 */
#define BTN_INPUT_START		36



#endif	//__DrumMachinePins__