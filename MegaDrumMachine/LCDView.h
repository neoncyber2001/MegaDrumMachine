// LCDView.h

#ifndef _LCDVIEW_h
#define _LCDVIEW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LCDView
{
 protected:


 public:
	void init();
};


#endif

