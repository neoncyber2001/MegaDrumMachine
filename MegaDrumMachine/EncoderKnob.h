// EncoderKnob.h

#ifndef _ENCODERKNOB_h
#define _ENCODERKNOB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

typedef void (*incrementfn)();
typedef void (*decrementfn)();
typedef void (*clickfn)();

#ifndef ENCODER_DEBOUNCE
	#define ENCODER_DEBOUNCE	10
#endif // !ENCODER_DEBOUNCE


class EncoderKnob
{
 protected:
	 volatile bool m_change = false;
	 volatile bool m_step = false;
	 long m_timer = 0;
	 int m_position = 0;
	 bool m_pressed = false;
	 bool m_justPressed = false;
	 bool m_justReleased = false;
	 int m_pinChanA; 
	 int m_pinChanB;
	 int m_pinPress;
	 bool m_isSetClick=false;
	 bool m_isSetInc = false;
	 bool m_isSetDec = false;
	 clickfn m_onClick;
	 incrementfn m_onInc;
	 decrementfn m_onDec;
 public:
	 void init(int chA, int chB, int click, voidFuncPtr isr, bool pullup = false);
	void tick();
};


#endif

