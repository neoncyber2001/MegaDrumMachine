// UIntWidget.h

#ifndef _UINTWIDGET_h
#define _UINTWIDGET_h

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
class UIntWidget : public LCDWidget
{
protected:

	unsigned int* m_boundVar;
	unsigned int m_scratchVar;

	unsigned int m_ubound = __INTMAX__;
	unsigned int m_lbound = -__INTMIN__;

public:
	UIntWidget(String* Label, byte row, byte col, unsigned int* boundValue, bool readOnly);

	UIntWidget(String* Label, byte row, byte col, unsigned int* boundValue, onSubmitFn submitCB, bool readOnly);
	// Inherited via LCDWidget
	virtual void NextValue() override;

	virtual void PreviousValue() override;

	virtual void SubmitValue() override;

	virtual void setSelected(bool val) override;

	virtual void setEdit(bool val) override;

	virtual void drawSelf(LiquidCrystal_I2C* lcd) override;

	virtual void updateSelf(LiquidCrystal_I2C* lcd) override;

	void setValueConstrain(unsigned int min, unsigned int max);

};


#endif
