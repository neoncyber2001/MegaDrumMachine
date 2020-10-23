// 
// 
// 

#include "BeatClock.h"

void BeatClock::m_recalc()
{
	m_millisPerStep = (60000 / m_BPM) / 16;
}

BeatClock::BeatClock()
{
	m_recalc();
}

void BeatClock::tick()
{
	if (m_isRunning) {
		if (millis() > m_nextStep) {
			m_nextStep = millis() + m_millisPerStep;
			m_isStep = true;
			m_steps++;
			m_beats = floor(m_steps / 4);
		}
		else {
			m_isStep = false;
		}
	}
}

void BeatClock::setBPM(unsigned int bpm)
{
	m_BPM = bpm;
	m_recalc();
}

void BeatClock::Start()
{
	m_isRunning = true;
	m_steps = 0;
	m_beats = 0;
	m_isStep = false;
	m_nextStep = millis() + m_millisPerStep;
}
