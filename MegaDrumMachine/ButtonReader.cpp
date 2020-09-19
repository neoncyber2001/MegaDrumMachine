// 
// 
// 

#include "ButtonReader.h"

void ButtonReader::begin(bool pullups)
{
	int useMode = 0;
	if (pullups) {
		useMode = INPUT_PULLUP;
	}
	else {
		useMode = INPUT;
	}
	for (int i = 0; i < 16; i++) {
		m_debouncer[i].attach(BTN_INPUT_START + i, useMode);
		m_debouncer[i].interval(25);
	}

#ifdef READ_RESIST_MATRIX
	pinMode(RBTN_PIN, INPUT);
#endif
}


void ButtonReader::tick()
{
	//copy current button state to previouse button state
	memcpy(&m_prevButtonState, &m_curButtonState, sizeof(uint8_t)*2);
	m_haveButtonsChangd = false;
	//clear the current button state
	m_curButtonState[0] = m_curButtonState[1] = 0x00;
	for (byte i = 0; i < 16; i++) {
		m_debouncer[i].update();
		if (m_debouncer[i].read()) {
			if (i % 2 == 0) {
				m_curButtonState[TOP_ROW] = m_curButtonState[TOP_ROW] | (0x01 << (int)floor(i / 2));
			}
			else {
				m_curButtonState[BOT_ROW] = m_curButtonState[BOT_ROW] | (0x01 << (int)floor(i / 2));
			}
		}
		if (m_debouncer[i].changed()) {
			if (!m_haveButtonsChangd) m_haveButtonsChangd = true;
		}
		
	}
	m_curButtonState[0] = m_curButtonState[0] ^ 0xFF;
	m_curButtonState[1] = m_curButtonState[1] ^ 0xFF;

}

#ifdef READ_RESIST_MATRIX

int ButtonReader::getRBtnRaw()
{
	return m_rbtnRAWValue;
}


int ButtonReader::readRBtn()
{
	m_rbtnRAWValue = analogRead(RBTN_PIN);
	bool oldPressed = m_isResistButonPressed;
	bool oldDown = m_isResistButonDown;
	bool oldRel = m_isResistButonReleased;
	if (m_rbtnRAWValue > 400) {
		m_isResistButonDown = true;
	}
	else {
		m_isResistButonDown = false;
	}
	if (!m_isResistButonDown && oldDown) {
		m_isResistButonReleased = true;
		m_isResistButonPressed = false;

	}
	else if (m_isResistButonDown && !oldDown) {
		m_isResistButonReleased = false;
		m_isResistButonPressed = true;
	}
	else {
		m_isResistButonReleased = false;
		m_isResistButonPressed = false;
	}
	if( (m_rbtnRAWValue > 400) && m_rbtnRAWValue <= 500) {
		m_resistPadIndex = 11;
	}
	else if (m_rbtnRAWValue > (RBTN_10_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_09_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 10;
	}
	else if (m_rbtnRAWValue > (RBTN_09_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_08_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 9;
	}
	else if (m_rbtnRAWValue > (RBTN_08_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_07_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 8;
	}
	else if (m_rbtnRAWValue > (RBTN_07_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_06_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 7;
	}
	else if (m_rbtnRAWValue > (RBTN_06_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_05_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 6;
	}
	else if (m_rbtnRAWValue > (RBTN_05_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_04_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 5;
	}
	else if (m_rbtnRAWValue > (RBTN_04_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_03_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 4;
	}
	else if (m_rbtnRAWValue > (RBTN_03_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_02_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 3;
	}
	else if (m_rbtnRAWValue > (RBTN_02_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_01_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 2;
	}
	else if (m_rbtnRAWValue > (RBTN_01_VAL - RBTN_TOLERANCE) && m_rbtnRAWValue <= (RBTN_00_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 1;
	}
	else if (m_rbtnRAWValue > (RBTN_00_VAL - RBTN_TOLERANCE)) {
		m_resistPadIndex = 0;
	}
	return m_resistPadIndex;
}


bool ButtonReader::haveRBtnsChanged()
{
	if (m_isResistButonPressed || m_isResistButonReleased) {
		return true;
	}
	else {
		return false;
	}
}

int ButtonReader::getRBtnPressed()
{
	if (m_isResistButonPressed) {
		return m_resistPadIndex;
	}
	else {
		return -1;
	}
}
int ButtonReader::getRBtnReleased()
{
	if (m_isResistButonReleased) {
		return m_resistPadIndex;
	}
	else {
		return -1;
	}

}
int ButtonReader::getRBtnDown()
{
	if (m_isResistButonDown) {
		return m_resistPadIndex;
	}
	else {
		return -1;
	}
}
#endif

void ButtonReader::checkButtons()
{
	tick();
}

bool ButtonReader::haveBtnsChanged()
{
	return m_haveButtonsChangd;
}

uint16_t ButtonReader::getButtonsPressed()
{
	uint16_t outb = 0x00;
	outb = outb | (!(m_prevButtonState[0] & m_curButtonState[0]))  << 8;
	outb = outb | (!(m_prevButtonState[1] & m_curButtonState[1]));
	return outb;
}

uint8_t ButtonReader::getRowPressed(bool row)
{

	uint8_t outb = 0x00;
	if (row == HIGH) {
		outb = outb | (!(m_prevButtonState[0] & m_curButtonState[0]));
	}
	else {
		outb = outb | (!(m_prevButtonState[1] & m_curButtonState[1]));
	}
	return outb;
}
uint16_t ButtonReader::getButtonsReleased()
{
	uint16_t outb = 0x00;
	outb=outb |(m_prevButtonState[0] ^ m_curButtonState[0]) << 8;
	outb = outb | (m_prevButtonState[1] ^ m_curButtonState[1]);

	return outb;
}
uint8_t ButtonReader::getRowReleased(bool row)
{
	uint8_t outb = 0x00;
	if (row == HIGH) {
		outb = outb | (m_prevButtonState[0] ^ m_curButtonState[0]);
	}
	else {
		outb = outb | (m_prevButtonState[1] ^ m_curButtonState[1]);
	}
	return outb;
}

uint16_t ButtonReader::getButtonsDown()
{
	uint16_t ob = 0x00;
	ob = ob | (m_curButtonState[0] << 8);
	ob = ob | m_curButtonState[1];
	return ob;
}


uint8_t ButtonReader::getRowDown(bool row)
{
	uint8_t ob = 0x00;
	if (row == HIGH) {
		ob = ob | (m_curButtonState[0]);
	}
	else {
		ob = ob | m_curButtonState[1];
	}
	return ob;
}

bool ButtonReader::isButtonPressed(byte index)
{
	if ((this->getButtonsPressed() & (0x01 << index)) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool ButtonReader::isButtonReleased(byte index)
{
	if ((this->getButtonsReleased() & (0x01 << index)) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool ButtonReader::isButtonDown(byte index)
{
	if ((this->getButtonsDown() & (0x01 << index)) > 0) {
		return true;
	}
	else {
		return false;
	}
}

