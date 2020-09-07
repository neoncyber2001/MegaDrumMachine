// LCDWidget.h

#ifndef _LCDWIDGET_h
#define _LCDWIDGET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

template <class T> class LCDWidget
{
 protected:
	 T* m_boundVar;
	 T m_scratchVar;
 public:

	void init();
};


#endif

