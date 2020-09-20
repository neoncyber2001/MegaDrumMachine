// LCDView.h

#ifndef _LCDVIEW_h
#define _LCDVIEW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <LiquidCrystal_I2C.h>
	#include "LCDWidget.h"
#else
	#include "WProgram.h"
#endif

class LCDView
{
 protected:
	 LCDWidget* m_widgets;
	 int m_count=0;
	 IVisibleWidget* m_indicators;
	 int m_ind_count=0;
	 int m_selected=0;
	 bool m_isEditMode = false;
	 bool m_drawRequired = true;
	 bool m_updateRequired=false;
	 byte m_rows;
	 byte m_cols;
	 String m_title;
	 LiquidCrystal_I2C*m_lcd;
 public:
	void begin(byte rows, byte cols, String title, int widgetCount, LCDWidget* widgetArry[], LiquidCrystal_I2C*lcd);
	void begin(byte rows, byte cols, String title, int widgetCount, LCDWidget* widgetArry[], int indicatorCount, IVisibleWidget* indicatorArray[], LiquidCrystal_I2C* lcd);
	void tick();
	void cmd_up();
	void cmd_down();
	void cmd_select();
	void cmd_esc();
	void updateView();
	void redrawView();
};


#endif

