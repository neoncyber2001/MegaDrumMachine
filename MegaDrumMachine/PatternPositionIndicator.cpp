// 
// 
// 

#include "PatternPositionIndicator.h"


PatternPositionIndicator::PatternPositionIndicator(int column, int row, int* var)
{
	m_col = column;
	m_row = row;
	m_boundVar = var;
}

void PatternPositionIndicator::drawSelf(LiquidCrystal_I2C *lcd)
{
	lcd->setCursor(m_col, m_row);
	lcd->print("[");
	char mark;
	for (int i = 0; i < 16; i++) lcd->print(" ");
	lcd->setCursor(m_col+1, m_row);
	for (int i = 0; i < *m_boundVar % 16; i++) {
		if (*m_boundVar % 4 == 0) {
			mark = (char)0xDB;
		}
		else {
			mark = (char)0xA5;
		}
		lcd->print(mark);
	}
	
	lcd->setCursor(m_col + 18, m_row);
	lcd->print("]");

}

void PatternPositionIndicator::updateSelf(LiquidCrystal_I2C * lcd)
{
	char mark;
	lcd->setCursor(m_col + 1, m_row);
	for (int i = 0; i < 16; i++) lcd->print(" ");
	lcd->setCursor(m_col + 1, m_row);
	for (int i = 0; i < *m_boundVar % 16; i++) {
		if (*m_boundVar % 4 == 0) {
			mark = (char)0xDB;
		}
		else {
			mark = (char)0xA5;
		}
		lcd->print(mark);
	}
}
