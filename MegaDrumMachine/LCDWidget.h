// LCDWidget.h

#ifndef _LCDWIDGET_h
#define _LCDWIDGET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

	#include <LiquidCrystal_I2C.h>
	#include"ISelectableWidget.h"
	#include"IVisibleWidget.h"
#else
	#include "WProgram.h"
#endif


#ifndef SELECTED_CHAR
	#define SELECTED_CHAR	0xA5
#endif
#ifndef EDIT_CHAR
	#define EDIT_CHAR	0xDB
#endif
class LCDWidget:public ISelectableWidget, public IVisibleWidget
{

protected:

	onSubmitFn m_onSubmit;
	bool m_isSetOnSubmit = false;
 public:

	 virtual bool isReadOnly() {
		 return m_isReadOnly;
	 };
	 virtual void setReadOnly(bool val) {
		 m_isReadOnly = val;
	 };

	 virtual void setOnSubmit(onSubmitFn func) override {
		 m_onSubmit = func;
		 m_isSetOnSubmit = true;
	 }

	 // Inherited via ISelectableWidget
	 virtual void NextValue() override = 0;
	 
	 virtual void PreviousValue() override = 0;

	 virtual void SubmitValue() override = 0;

	 virtual void setSelected(bool val) override = 0;

	 virtual void setEdit(bool val) override = 0;


	 // Inherited via IVisibleWidget
	 virtual void drawSelf(LiquidCrystal_I2C *lcd) override = 0;

	 virtual void updateSelf(LiquidCrystal_I2C * lcd) override = 0;

};


#endif

