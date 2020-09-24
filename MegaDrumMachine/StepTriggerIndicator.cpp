// 
// 
// 

#include "StepTriggerIndicator.h"

StepTriggerIndicator::StepTriggerIndicator(int column, int row, byte* var)
{
	m_row = row;
	m_col = column;
	m_boundVar = var;
}

void StepTriggerIndicator::drawSelf(LiquidCrystal_I2C *lcd)
{
	lcd->setCursor(m_col, m_row);
	lcd->print("[");
	for (int i = 0; i < 8; i++) {
		char mark;
		if ((*m_boundVar & (0x01 << i)) != 0) {
			mark = (char)'#';
		}
		else {
			mark = (char)'-';
		}
		lcd->print(mark);
	}
	lcd->print("]");
}

void StepTriggerIndicator::updateSelf(LiquidCrystal_I2C * lcd)
{
	lcd->setCursor(m_col, m_row);
	lcd->print("[");
	for (int i = 0; i < 8; i++) {
		char mark;
		if ((*m_boundVar & (0x01 << i)) != 0) {
			mark = (char)'#';
		}
		else {
			mark = (char)'-';
		}
		lcd->print(mark);
	}
	lcd->print("]");
}
