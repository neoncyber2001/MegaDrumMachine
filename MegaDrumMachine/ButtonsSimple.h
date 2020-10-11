// ButtonsSimple.h

#ifndef _BUTTONSSIMPLE_h
#define _BUTTONSSIMPLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include <Bounce2.h>
#else
	#include "WProgram.h"
#endif

class ButtonsSimple
{
 protected:
	 byte m_Values = 0x00;
	 byte m_History = 0x00;
	 byte m_buttons = 0;
	 bool m_isStarted = false;
 public:
	 void Read();
	 byte isDown() {
		return m_Values;
	}
	byte isPressed() {
		return (m_Values ^ m_History);
	}
	byte isReleased() {
		return (m_Values ^ 0xff)^m_History;
	}
};



#endif

