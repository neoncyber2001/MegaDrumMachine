// PatternBank.h

#ifndef _PATTERNBANK_h
#define _PATTERNBANK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DrumPattern.h"

class PatternBank
{
 protected:
	 DrumPattern m_patterns[16];

 public:
	void init();
	DrumPattern* getPatternPtr(uint8_t slot);
	void loadPatterns(DrumPattern* data[], uint8_t pats);
	bool getPatterns(DrumPattern* data[], uint8_t* pats);
};


#endif

