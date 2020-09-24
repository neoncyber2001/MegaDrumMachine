// 
// 
// 

#include "IconIndicator.h"

IconIndicator::IconIndicator(int column, int row, char icon, bool* var)
{
	m_row = row;
	m_col = column;
	m_icon = icon;
	m_boundVar = var;
}

void IconIndicator::drawSelf(LiquidCrystal_I2C *lcd)
{
	lcd->setCursor(m_col, m_row);
	char mark;
	if (*m_boundVar==true) {
		mark = m_icon;
	}
	else {
		mark = (char)' ';
	}
	lcd->print(mark);
}

void IconIndicator::updateSelf(LiquidCrystal_I2C *lcd)
{
	lcd->setCursor(m_col, m_row);
	char mark;
	if (*m_boundVar == true) {
		mark = m_icon;
	}
	else {
		mark = (char)' ';
	}
	lcd->print(mark);
}
