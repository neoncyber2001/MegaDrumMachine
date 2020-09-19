// BtnPad.h

#ifndef _BTNPAD_h
#define _BTNPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Bounce2.h>
#include <WString.h>

#ifndef BTN_PAD_INVERT
	#define BTN_PAD_INVERT		0
#endif
//ASmaller Geraric Button State Reporting Object
class BtnPad
{
 protected:
	 int*m_btnPins;
	 int m_btnCount;
	 byte* m_Pressed;
	 byte* m_JustPressed;
	 byte* m_Released;
	 int m_buffSize;
	 Bounce* m_debouncer;

 public:
	/// <summary>
	/// Initialize the BtnPad object
	/// </summary>
	/// <param name="pins">Array of arduino Pin Numbers which will be used as button inputs.</param>
	/// <param name="pinCount"></param>
	/// <param name="pullups"></param>
	void init(int*pins,int pinCount, bool pullups=false);
	void tick();
	int getBufferSize() { return m_buffSize; };
	void getPressedButtons(byte* buffer);
	void getJustPressedButtons(byte* buffer);
	void getReleasedButtons(byte* buffer);
	bool isButtonPressed(int index);
	bool isButtonJustPressed(int index);
	bool isButtonReleased(int index);
	~BtnPad();
};

#endif

