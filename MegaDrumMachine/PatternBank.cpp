// 
// 
// 

#include "PatternBank.h"

void PatternBank::init()
{


}

DrumPattern* PatternBank::getPatternPtr(uint8_t slot)
{
	return &m_patterns[slot];
}

void PatternBank::loadPatterns(DrumPattern* data[], uint8_t pats)
{
	if (pats < 16) {
		for (int i = 0; i < pats; i++) {
			m_patterns[i] = *data[i];
		}
	}
}

bool PatternBank::getPatterns(DrumPattern* data[], uint8_t* pats)
{
	*pats = 0;
	for (int i = 0; i < 16; i++) {
		if (m_patterns[i].isInitialized()) {
			pats++;
			*data[*pats] = m_patterns[i];
		}
	}
	if (*pats > 0) {
		return true;
	}
	else {
		return false;
	}
}



