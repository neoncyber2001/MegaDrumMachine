// LCDWidget.h

#ifndef _LCDWIDGET_h
#define _LCDWIDGET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#include <LiquidCrystal_I2C.h>
#else
	#include "WProgram.h"
#endif


#ifndef SELECTED_CHAR
	#define SELECTED_CHAR	0xA5
#endif
#ifndef EDIT_CHAR
	#define EDIT_CHAR	0xDB
#endif
//template <typename T>
class LCDWidget
{

protected:
	byte m_row;
	byte m_col;
	String* m_label;
	bool m_isSelected;
	bool m_isEditing;

 public:
	virtual void NextValue()=0;
	virtual void PreviousValue()=0;
	virtual void SubmitValue()=0;
	virtual void setSelected(bool val)=0;
	virtual void setEdit(bool val)=0;
	virtual void drawSelf(LiquidCrystal_I2C lcd) = 0;
	virtual void updateSelf(LiquidCrystal_I2C lcd) = 0;
};


#endif

