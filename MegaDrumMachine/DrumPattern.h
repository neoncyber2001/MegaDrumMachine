#ifndef _DRUMPATTERN_h
#define _DRUMPATTERN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
class DrumPattern
{
public:
	void init();
	bool isInitialized();
	void setTrigger(byte step, byte channel);
	byte getStep(byte step);
	void setStep(byte step, byte data);
	byte* getRawPattern();
	void clearStep(byte step);
	void clearPattern();
	byte getNextPattern() { return m_nextPattern; }
	void setNextPattern(byte value) { m_nextPattern = value; }
private:
	bool m_isInitialized=false;
	byte m_rawPattern[16];
	byte m_nextPattern;
};
#endif

