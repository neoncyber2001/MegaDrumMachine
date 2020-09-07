// DrumKit.h

#ifndef _DRUMKIT_h
#define _DRUMKIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define KITOFFSET		(16*16+2)
#define KITSLOTS		2
class DrumKit
{
 protected:
	 uint16_t kit[8];
	 byte gain[8];

 public:
	 DrumKit(uint16_t sampleA, uint16_t sampleB, uint16_t sampleC, uint16_t sampleD, uint16_t sampleE, uint16_t sampleF, uint16_t sampleG, uint16_t sampleH);
	 DrumKit();

	 virtual uint16_t getSample(uint8_t slot) { return kit[slot]; }
	 virtual void setSample(uint8_t slot, uint16_t val) { kit[slot] = val; }

	 virtual byte getGain(uint8_t slot) { return gain[slot]; }
	 virtual void setKickGain(uint8_t slot, uint16_t val) { gain[slot] = val; }

	 virtual uint16_t* getSampPtr() { return kit; }
	 virtual byte* getGainPtr() { return gain; }

};



#endif

