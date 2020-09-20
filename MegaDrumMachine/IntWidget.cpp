// 
// 
// 

#include "IntWidget.h"

IntWidget::IntWidget(String* Label, byte row, byte col, int* boundValue, bool readOnly = false)
{
	m_label = Label;
	m_row = row;
	m_col = col;
	m_boundVar = boundValue;
	m_scratchVar = *boundValue;
	m_isSelected = false;
	m_isEditing = false;
	m_isReadOnly = readOnly;
}

IntWidget::IntWidget(String* Label, byte row, byte col, int* boundValue, onSubmitFn submitCB, bool readOnly)
{
	m_label = Label;
	m_row = row;
	m_col = col;
	m_boundVar = boundValue;
	m_scratchVar = *boundValue;
	setOnSubmit(submitCB);
	m_isSelected = false;
	m_isEditing = false;
	m_isReadOnly = readOnly;
}

void IntWidget::NextValue()
{
	if (m_isEditing) {
		if (m_scratchVar < m_ubound) {
			m_scratchVar++;
		}
	}
}

void IntWidget::PreviousValue()
{
	if (m_isEditing) {
		if (m_scratchVar > m_lbound) {
			m_scratchVar--;
		}
	}
}

void IntWidget::SubmitValue()
{
	*m_boundVar = m_scratchVar;
	if (m_isSetOnSubmit) {
		(m_onSubmit());
	}
}

void IntWidget::setSelected(bool val)
{
	m_isSelected = val;
}

void IntWidget::setEdit(bool val)
{
	m_isEditing = val;
}

void IntWidget::drawSelf(LiquidCrystal_I2C lcd)
{
	lcd.setCursor(m_col, m_row);
	if (m_label->length() > 4) {
		lcd.print(m_label->substring(0, 4));
	}
	lcd.print(":");
	if (m_isEditing) {
		lcd.print(m_scratchVar);
		lcd.print("  ");
	}
	else {
		lcd.print(*m_boundVar);
	}
	if (m_isSelected && !m_isEditing) {
		lcd.setCursor(m_col + 8, m_row);
		lcd.print((char)SELECTED_CHAR);
	}
	else if (m_isSelected && m_isEditing) {
		lcd.setCursor(m_col + 8, m_row);
		lcd.print((char)EDIT_CHAR);
	}
	else {
		lcd.setCursor(m_col + 8, m_row);
		lcd.print(" ");
	}
}

void IntWidget::updateSelf(LiquidCrystal_I2C lcd)
{
	lcd.setCursor(m_col + 5, m_row);
	if (m_isEditing) {
		lcd.print(m_scratchVar);
	}
	else {
		lcd.print(*m_boundVar);
	}
	lcd.print("  ");
	if (m_isSelected && !m_isEditing) {
		lcd.setCursor(m_col + 8, m_row);
		lcd.print((char)SELECTED_CHAR);
	}
	else if (m_isSelected && m_isEditing) {
		lcd.setCursor(m_col + 8, m_row);
		lcd.print((char)EDIT_CHAR);
	}
	else {
		lcd.setCursor(m_col + 8, m_row);
		lcd.print(" ");
	}
}

void IntWidget::setValueConstrain(int min, int max)
{
	if (max > min) {
		m_ubound = max;
		m_lbound = min;
	}
}
