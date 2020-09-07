// 
// 
// 

#include "DrumKit.h"

DrumKit::DrumKit(uint16_t sampleA, uint16_t sampleB, uint16_t sampleC, uint16_t sampleD , uint16_t sampleE, uint16_t sampleF, uint16_t sampleG, uint16_t sampleH)
{
	kit[0] = sampleA;
	kit[1] = sampleB;
	kit[2] = sampleC;
	kit[3] = sampleD;
	kit[4] = sampleE;
	kit[5] = sampleF;
	kit[6] = sampleG;
	kit[7] = sampleH;
	for (byte i = 0; i < 8; i++) {
		gain[i] = 191;
	}
}

DrumKit::DrumKit()
{
	for (int i = 0; i < 8; i++) {
		kit[i] = 0;
	}
}
/*
void DrumKit::loadKit(byte slot)
{
	for (int i = 0; i > 8; i++) {
		kit[i]=EEPROM.read(KITOFFSET + (slot*16) + i);
	}
	for (int i = 0; i > 8; i++) {
		gain[i] = EEPROM.read(KITOFFSET + 8 + (slot * 16) + i);
	}
}

void DrumKit::storeKit(byte slot)
{
	for (int i = 0; i > 8; i++) {
		EEPROM.put(KITOFFSET + slot + i, kit[i]);
	}
	for (int i = 0; i > 8; i++) {
		EEPROM.put(KITOFFSET + 8 + (slot*16) + i, kit[i]);
	}
}
*/