#include "DrumPattern.h"



void DrumPattern::init()
{
	this->clearPattern();
	m_isInitialized = true;
}

bool DrumPattern::isInitialized()
{
	return m_isInitialized;
}

void DrumPattern::setTrigger(byte step, byte channel)
{
	if (channel < 8) {
		byte ch = 0x01 << channel;
		m_rawPattern[step] = m_rawPattern[step] ^ ch;
	}
	
}

byte DrumPattern::getStep(byte step)
{
	return m_rawPattern[step];
}

void DrumPattern::setStep(byte step, byte data)
{
	m_rawPattern[step] = data;
}

byte* DrumPattern::getRawPattern()
{
	return m_rawPattern;
}

void DrumPattern::clearStep(byte step)
{
	m_rawPattern[step] = 0x00;
}

void DrumPattern::clearPattern()
{
	for (int i = 0; i < 16.; i++) {
		m_rawPattern[i] = 0x00;
	}
}
