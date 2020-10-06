// ButtonReader.h

#ifndef _BUTTONREADER_h
#define _BUTTONREADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Bounce2.h>

#ifndef BTN_INPUT_START
#define BTN_INPUT_START		36
#endif

/*#ifndef Bounce2_h
#error Bounce2 required.
#endif // !Bounce2_h*/



#define TOP_ROW	0
#define BOT_ROW 1


class ButtonReader
{
 protected:
	 uint8_t m_curButtonState[2] = { 0x00,0x00 };
	 uint8_t m_prevButtonState[2] = { 0x00,0x00 };
	 Bounce m_debouncer[16];
	 bool m_haveButtonsChangd = false;

 public:
	void begin(bool pullups = false);
	void tick();
	void checkButtons();
	bool haveBtnsChanged();
	uint16_t getButtonsPressed();
	uint8_t getRowPressed(bool row);
	uint16_t getButtonsReleased();
	uint8_t getRowReleased(bool row);
	uint16_t getButtonsDown();
	uint8_t getRowDown(bool row);
	bool isButtonPressed(byte index);
	bool isButtonReleased(byte index);
	bool isButtonDown(byte index);

};

#endif

