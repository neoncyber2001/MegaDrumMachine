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

#define RBTN_00_VAL		1000
#define RBTN_01_VAL		930
#define RBTN_02_VAL		850
#define RBTN_03_VAL		790
#define RBTN_04_VAL		730
#define RBTN_05_VAL		680
#define RBTN_06_VAL		640
#define RBTN_07_VAL		600
#define RBTN_08_VAL		570
#define RBTN_09_VAL		540
#define RBTN_10_VAL		510
#define RBTN_11_VAL		480

#define RBTN_TOLERANCE	30

#ifndef RBTN_PIN
 #define RBTN_PIN		A10
#endif

#ifndef RBTN_READ_MOD
	#define RBTN_READ_MOD	2
#endif // !RBTN_READ_MOD


class ButtonReader
{
 protected:
	 uint8_t m_curButtonState[2] = { 0x00,0x00 };
	 uint8_t m_prevButtonState[2] = { 0x00,0x00 };
	 Bounce m_debouncer[16];
	 bool m_haveButtonsChangd = false;
	 
	 int m_rbtnRAWValue = 0;
	 bool m_isResistButonDown = false;
	 bool m_isResistButonPressed = false;
	 bool m_isResistButonReleased = false;
	 uint8_t m_resistPadIndex = 0;

 public:
	void begin(bool pullups = false);
	void doScan();
	int readRBtn();
	void checkButtons();
	bool haveBtnsChanged();
	bool haveRBtnsChanged();
	uint16_t getButtonsPressed();
	uint8_t getRowPressed(bool row);
	uint16_t getButtonsReleased();
	uint8_t getRowReleased(bool row);
	uint16_t getButtonsDown();
	uint8_t getRowDown(bool row);
	int getRBtnPressed();
	int getRBtnReleased();
	int getRBtnDown();
	bool isButtonPressed(byte index);
	bool isButtonReleased(byte index);
	bool isButtonDown(byte index);
	int getRBtnRaw();
};

#endif

