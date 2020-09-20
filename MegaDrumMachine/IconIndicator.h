// IconIndicator.h

#ifndef _ICONINDICATOR_h
#define _ICONINDICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include "IVisibleWidget.h"
#include <LiquidCrystal_I2C.h>

#else
	#include "WProgram.h"
#endif
/// <summary>
/// Displays the value of a boolean variable;
/// </summary>
class IconIndicator:public IVisibleWidget
{
 protected:
	 int m_row;
	 int m_col;
	 char m_icon;
	 bool* m_boundVar;
 public:
	 IconIndicator(int column, int row, char icon, bool* var);
	 // Inherited via IVisibleWidget
	 virtual void drawSelf(LiquidCrystal_I2C lcd);
	 virtual void updateSelf(LiquidCrystal_I2C lcd);
};
#endif
