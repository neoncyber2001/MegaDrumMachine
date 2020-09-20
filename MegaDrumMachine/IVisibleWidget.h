// IVisibleWidget.h

#ifndef _IVISIBLEWIDGET_h
#define _IVISIBLEWIDGET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class IVisibleWidget
{
 protected:
	 byte m_row;
	 byte m_col;
	 String* m_label;


 public:
	 virtual void drawSelf(LiquidCrystal_I2C lcd) = 0;
	 virtual void updateSelf(LiquidCrystal_I2C lcd) = 0;
	 
};

#endif
