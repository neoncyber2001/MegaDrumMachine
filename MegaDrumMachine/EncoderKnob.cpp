// 
// 
// 

#include "EncoderKnob.h"
void EncoderKnob::init(int chA, int chB, int click, voidFuncPtr isr, bool pullup = false)
{
	attachInterrupt(chA, , RISING);
	
}

void EncoderKnob::tick()
{
	if (m_change) {
		if (m_step) {
			m_position++;
			if(m_isSetInc)(m_onInc)();
		}
		if (m_step) {
			m_position--;
			if (m_isSetDec)(m_onDec)();
		}
	}
	bool click = digitalRead(m_pinPress);
	if (click) {
		if (!m_pressed) {
			m_justPressed = true;
			m_pressed = true;
			if (m_isSetClick)(m_onClick)();
		}
		else {
			m_justPressed= false;
		}
	}
	if (!click && m_pressed) {
		m_justReleased = true;
		m_pressed = false;
	}
	if(m_timer>0) m_timer--;
}



