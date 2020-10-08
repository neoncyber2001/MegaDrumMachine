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
#define PIN_ROTARY_CLICK		26
#define PIN_ROTARY_A			22
#define PIN_ROTARY_B			23

/**
 * Mode Toggle Switch
 * PLAY = Play
 * PKIT	= Kit
 * No Connection = Program
 */
#define PIN_MODETOG_A			24
#define PIN_MODETOG_B			25
#define MODE_PLAY				PIN_MODETOG_A
#define MODE_KIT				PIN_MODETOG_B

/**
 * PushButtons
 * BTNA		Metronome On/Off
 * BTNB
 * BTNRED	Play/Stop
 */

#define PIN_BTN_RED			28
#define PIN_BTN_A			31
#define PIN_BTN_B			29
#define PIN_BTN_C			27

/**
 * WavTrigger
 */
#define __WT_USE_SERIAL1__

/**
 *  Button Reader
 */
#define BTN_INPUT_START		36



#endif	//__DrumMachinePins__