// SelectableWidget.h

#ifndef _ISELECTABLEWIDGET_h
#define _ISELECTABLEWIDGET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <LiquidCrystal_I2C.h>
	#include "LCDWidget.h"
#else
	#include "WProgram.h"
#endif
typedef void (*onSubmitFn)();


class ISelectableWidget
{
 protected:
	 bool m_isSelected;
	 bool m_isEditing;
	 bool m_isReadOnly = false;
 public:
	 virtual void NextValue() = 0;
	 virtual void PreviousValue() = 0;
	 virtual void SubmitValue() = 0;
	 virtual void setSelected(bool val) = 0;
	 virtual void setEdit(bool val) = 0;
	 virtual bool isReadOnly() = 0;
	 virtual void setReadOnly(bool val) = 0;
	 virtual void setOnSubmit(onSubmitFn func) = 0;
};


#endif

