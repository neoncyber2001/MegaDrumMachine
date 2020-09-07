#pragma once

#ifndef _LCDView_h
#define _LCDView_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class LCDView
{
public:
	void init();
private:
	uint8_t itemIndex = 0;
	uint8_t totalItems;
	
};

#endif

