// StepTriggerIndicator.h

#ifndef _STEPTRIGGERINDICATOR_h
#define _STEPTRIGGERINDICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include "IVisibleWidget.h"
#include <LiquidCrystal_I2C.h>
#else
	#include "WProgram.h"
#endif

class StepTriggerIndicator:public IVisibleWidget
{
 protected:
	 int m_row;
	 int m_col;
	 byte* m_boundVar;

 public:
	 StepTriggerIndicator(int column, int row, byte* var);
	 // Inherited via IVisibleWidget
	 virtual void drawSelf(LiquidCrystal_I2C *lcd) override;
	 virtual void updateSelf(LiquidCrystal_I2C *lcd) override;
};

#endif

