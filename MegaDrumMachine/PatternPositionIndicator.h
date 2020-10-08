// PatternPositionIndicator.h

#ifndef _PATTERNPOSITIONINDICATOR_h
#define _PATTERNPOSITIONINDICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "IVisibleWidget.h"
	#include <LiquidCrystal_I2C.h>
#else
	#include "WProgram.h"
#endif

class PatternPositionIndicator:public IVisibleWidget
{
 protected:
	 int m_row;
	 int m_col;
	 char m_sixteenth;
	 char m_quarter;
	 unsigned int* m_boundVar;

 public:
	 PatternPositionIndicator(int column, int row, unsigned int* var);

	 // Inherited via IVisibleWidget
	 virtual void drawSelf(LiquidCrystal_I2C *lcd) override;

	 virtual void updateSelf(LiquidCrystal_I2C *lcd) override;

};
#endif

