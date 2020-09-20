// IntWidget.h

#ifndef _INTWIDGET_h
#define _INTWIDGET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#include <LiquidCrystal_I2C.h>
#include "LCDWidget.h"
#else
	#include "WProgram.h"
#endif

#ifdef __AVR__
	#define __INTMIN__	-32767;
	#define __INTMAX__	32767;
#endif // __AVR__

#ifdef __SAMD51__
	#define __INTMIN__	-2147483647
	#define __INTMAX__	2147483647
#endif
class IntWidget: public LCDWidget
{
protected:

	int* m_boundVar;
	int m_scratchVar;

	int m_ubound = __INTMAX__;
	int m_lbound = -__INTMIN__;

public:
	IntWidget(String* Label, byte row, byte col, int* boundValue, bool readOnly=false);

	IntWidget(String* Label, byte row, byte col, int* boundValue, onSubmitFn submitCB, bool readOnly);
	// Inherited via LCDWidget
	virtual void NextValue() override;

	virtual void PreviousValue() override;

	virtual void SubmitValue() override;

	virtual void setSelected(bool val) override;

	virtual void setEdit(bool val) override;

	virtual void drawSelf(LiquidCrystal_I2C lcd) override;

	virtual void updateSelf(LiquidCrystal_I2C lcd) override;

	void setValueConstrain(int min, int max);

};


#endif

