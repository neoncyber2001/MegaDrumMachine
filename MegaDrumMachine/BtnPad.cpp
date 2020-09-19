// 
// 
// 

#include "BtnPad.h"

void BtnPad::init(int *pins, int pinCount, bool pullups)
{
	m_buffSize = floor(pinCount / 8) + 1;
	m_btnPins = pins;
	m_btnCount = pinCount;
	
	//allocate state buffers
	m_debouncer = (Bounce*)malloc((size_t)m_buffSize * sizeof(Bounce));
	m_Pressed = (byte*)malloc((size_t)m_buffSize * sizeof(byte));
	m_JustPressed = (byte*)malloc((size_t)m_buffSize * sizeof(byte));
	m_Released = (byte*)malloc((size_t)m_buffSize * sizeof(byte));

	int mark;
	if (pullups) {
		mark = INPUT_PULLUP;
	}
	else {
		mark = INPUT;
	}

	//setPinModes
	for (int i = 0; i < m_btnCount; i++) {
		pinMode(m_btnPins[i], mark);
	}
}

void BtnPad::tick()
{
	byte* scratchBuffer;
	scratchBuffer = (byte*)calloc((size_t)m_buffSize,sizeof(byte));
	for (int i = 0; i < m_btnCount; i++) {
#if BTN_PAD_INVERT == 0
		if (digitalRead(m_btnPins[i])) {
			*scratchBuffer = *scratchBuffer | (0x1 << i);
		}
#elif BTN_PAD_INVERT == 1
		if (!digitalRead(m_btnPins[i])) {
				*scratchBuffer = *scratchBuffer | (0x1 << i);
		}
#endif
	}

	*m_JustPressed = (~*m_Pressed)&*scratchBuffer;
	*m_Released = *m_Pressed ^ *scratchBuffer;
	*m_Pressed = *scratchBuffer;
}

 void BtnPad::getPressedButtons(byte* buffer) {
	for (int i = 0; i < m_buffSize; i++) {
		buffer[i] = m_Pressed[i];
	};
}

void BtnPad::getJustPressedButtons(byte* buffer) {
	for (int i = 0; i < m_buffSize; i++) {
		buffer[i] = m_JustPressed[i];
	}
}

 void BtnPad::getReleasedButtons(byte* buffer) {
	for (int i = 0; i < m_buffSize; i++) {
		buffer[i] = m_Pressed[i];
	}
}

 bool BtnPad::isButtonPressed(int index) {
	if ((*m_Pressed & (0x01 << index)) != 0) {
		return true;
	}
	else {
		return false;
	}
}

 bool BtnPad::isButtonJustPressed(int index) {
	if ((*m_JustPressed & (0x01 << index)) != 0) {
		return true;
	}
	else {
		return false;
	}
}

inline bool BtnPad::isButtonReleased(int index) {
	if ((*m_Released & (0x01 << index)) != 0) {
		return true;
	}
	else {
		return false;
	}
}

BtnPad::~BtnPad()
{
	free(m_Pressed);
	free(m_JustPressed);
	free(m_Released);
	free(m_debouncer);
}
