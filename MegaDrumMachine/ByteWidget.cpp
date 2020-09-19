// 
// 
// 

#include "ByteWidget.h"

ByteWidget::ByteWidget(String* Label, byte row, byte col, byte* boundValue)
{
	m_label = Label;
	m_row = row;
	m_col = col;
	m_boundVar = boundValue;
	m_scratchVar = *boundValue;
	m_isSelected = false;
	m_isEditing = false;
}

void ByteWidget::NextValue()
{
	if (m_isEditing) {
		if (m_scratchVar < 255) {
			m_scratchVar++;
		}
	}
}

void ByteWidget::PreviousValue()
{
	if (m_isEditing) {
		if (m_scratchVar > 0) {
			m_scratchVar--;
		}
	}
}

void ByteWidget::SubmitValue()
{
	*m_boundVar = m_scratchVar;
}

void ByteWidget::setSelected(bool val)
{
	m_isSelected = val;
}

void ByteWidget::setEdit(bool val)
{
	m_isEditing = val;
}

void ByteWidget::drawSelf(LiquidCrystal_I2C lcd)
{
	lcd.setCursor(m_col, m_row);
	lcd.print(m_label->substring(0, 4));
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

void ByteWidget::updateSelf(LiquidCrystal_I2C lcd)
{
	lcd.setCursor(m_col + 5, m_row);
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
