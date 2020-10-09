// 
// 
// 

#include "ButtonsSimple.h"
/// <summary>
/// 
/// </summary>
ButtonsSimple::ButtonsSimple()
{
	m_isStarted = false;
}
 
/// <summary>
/// 
/// </summary>
/// <param name="btns"></param>
ButtonsSimple::ButtonsSimple(int* btns[8])
{
	for (int i = 0; i < 8; i++) {
		m_btnReaders[i] = *btns[i];
	}
}

void ButtonsSimple::Add(int pin, int PullUp)
{
	if (m_buttons < 8 && !m_isStarted) {
		pinMode(pin, PullUp);
		m_btnReaders[m_buttons] = pin;
		//m_btnReaders[m_buttons] = Bounce(pin, 10);
		m_buttons++;
	}
}

void ButtonsSimple::Start()
{
	m_isStarted = true;
}

void ButtonsSimple::Read()
{

	if (m_isStarted) {
		m_History = m_Values;
		m_Values = 0x00;
		for (int i = 0; i < m_buttons; i++) {
			if (digitalRead(m_btnReaders[i])) {
				m_Values = m_Values | (0x01 << i);
			};
		}
	}
}
