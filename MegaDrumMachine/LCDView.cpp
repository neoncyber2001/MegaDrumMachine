// 
// 
// 

#include "LCDView.h"


LCDView::LCDView(byte rows, byte cols, String title, int widgetCount, LCDWidget* widgetArry[], LiquidCrystal_I2C*lcd)
{
	m_rows = rows;
	m_cols = cols;
	m_title = title;
	m_count = widgetCount;
	m_widgets = *widgetArry;
	m_lcd = lcd;
}

LCDView::LCDView(byte rows, byte cols, String title, int widgetCount, LCDWidget* widgetArry[], int indicatorCount, IVisibleWidget* indicatorArray[], LiquidCrystal_I2C* lcd)
{
	m_ind_count = indicatorCount;
	m_indicators = *indicatorArray;
	LCDView(rows, cols, title, widgetCount, widgetArry, lcd);
}

void LCDView::tick()
{
	if (m_drawRequired) {
		m_lcd->clear();
		m_lcd->setCursor(0, 0);
		m_lcd->print("<");
		m_lcd->print(m_title);
		m_lcd->print(">");
		for (int i = 0; i < m_count; i++) {
			m_widgets[i].drawSelf(*m_lcd);
		}
		m_drawRequired = false;
	}
	if (m_updateRequired) {
		for (int i = 0; i < m_count; i++) {
			m_widgets[i].updateSelf(*m_lcd);
		}
		m_updateRequired = false;
	}
}

void LCDView::cmd_up()
{
	if (!m_isEditMode && m_selected < m_count) {
		m_widgets[m_selected].setSelected(false);
		m_selected++;
		m_widgets[m_selected].setSelected(true);
		updateView();
	}
	else if (m_isEditMode) {
		m_widgets[m_selected].NextValue();
		updateView();
	}
}

void LCDView::cmd_down()
{
	if (!m_isEditMode && m_selected > 0) {
		m_widgets[m_selected].setSelected(false);
		m_selected--;
		m_widgets[m_selected].setSelected(true);
		updateView();
	}
	else if (m_isEditMode) {
		m_widgets[m_selected].PreviousValue();
		updateView();
	}
}

void LCDView::cmd_select()
{
	if (!m_isEditMode) {
		if (!m_widgets[m_selected].isReadOnly()) {
			m_widgets[m_selected].setEdit(true);
			m_isEditMode = true;
		}
	}
	else {
		m_widgets[m_selected].setEdit(true);
		m_widgets[m_selected].SubmitValue();
		m_isEditMode = true;
		updateView();
	}

}

void LCDView::cmd_esc()
{
}

void LCDView::updateView()
{
	m_updateRequired = true;
}

void LCDView::redrawView()
{
	m_drawRequired = true;
}
