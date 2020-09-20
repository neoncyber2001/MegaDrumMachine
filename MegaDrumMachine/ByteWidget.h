// ByteWidget.h

#ifndef _BYTEWIDGET_h
#define _BYTEWIDGET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#include <LiquidCrystal_I2C.h>
#include "LCDWidget.h"
#else
	#include "WProgram.h"
#endif

class ByteWidget: public LCDWidget
{
 protected:
	
	 byte* m_boundVar;
	 byte m_scratchVar;
	 byte m_row;
	 byte m_col;
	 String* m_label;
 public:
	 ByteWidget(String* Label, byte row, byte col, byte* boundValue, bool readOnly = false);

	 // Inherited via LCDWidget
	 virtual void NextValue() override;

	 virtual void PreviousValue() override;

	 virtual void SubmitValue() override;

	 virtual void setSelected(bool val) override;

	 virtual void setEdit(bool val) override;

	 virtual void drawSelf(LiquidCrystal_I2C lcd) override;

	 virtual void updateSelf(LiquidCrystal_I2C lcd) override;

};

#endif

