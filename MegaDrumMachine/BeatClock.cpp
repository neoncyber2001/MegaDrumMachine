// 
// 
// 

#include "BeatClock.h"

unsigned long BeatClock::m_CalculatePulseTime()
{
	return  round((1000000/(m_tempo / 60))/m_ppqn);
}

BeatClock::BeatClock()
{
	m_isClockMaster = true;
	m_isTrigger = false;
	m_isUartMidi = false;
	m_isPulseSet = false;
	m_isStepSet = false;
	m_isBeatSet = false;
	m_onPulse = nullptr;
	m_onStep = nullptr;
	m_onBeat = nullptr;

	m_pulses = 0;
	m_tempo = 120;
	m_ppqn = 24;
	m_isRunning = false;
	m_nextPulse = 0;
	m_pulseTime = this->m_CalculatePulseTime();
	m_SyncPin = CLOCK_TRIGGER_PIN;
	pinMode(m_SyncPin, OUTPUT);
}

void BeatClock::init()
{
	/*
	 bool m_isClockMaster;
	 bool m_isTrigger;
	 bool m_isUartMidi;
	 bool m_isPulseSet;
	 bool m_isStepSet;
	 bool m_isBeatSet;
	 unsigned int m_pulses;
	 onPulseFn* m_onPulse;
	 onStepFn* m_onStep;
	 onBeatFn* m_onBeat;
	 int m_tempo; //in bpm
	 int m_ppqn; //Pulses Per Quarter Note
	 bool m_isRunning;
	 unsigned long m_nextPulse;
	 unsigned long m_pulseTime;
	 */
	this->init(true, false, false);
}

void BeatClock::init(bool master, bool midi, bool trigger)
{
	m_isClockMaster = master;
	m_isTrigger = trigger;
	m_isUartMidi = midi;
	m_isPulseSet = false;
	m_isStepSet = false;
	m_isBeatSet = false;
	m_onPulse = nullptr;
	m_onStep = nullptr;
	m_onBeat = nullptr;

	m_pulses = 0;
	m_tempo = 120;
	m_ppqn = 24;
	m_isRunning = false;
	m_nextPulse = 0;
	m_pulseTime = this->m_CalculatePulseTime();
	m_SyncPin = CLOCK_TRIGGER_PIN;
	pinMode(m_SyncPin, OUTPUT);
}



void BeatClock::setOnPulse(onPulseFn userFn)
{
	if (!m_isRunning) {
		m_onPulse = userFn;
		m_isPulseSet = true;
	}
}

void BeatClock::setOnStep(onStepFn userFn)
{
	if (!m_isRunning) {
		m_onStep = userFn;
		m_isStepSet = true;
	}
}

void BeatClock::setOnBeat(onBeatFn userFn)
{
	if (!m_isRunning) {
		m_onBeat = userFn;
		m_isBeatSet = true;
	}
}

void BeatClock::tick()
{
	if (m_isRunning) {
		if (__TIMER > m_nextPulse) {
			m_nextPulse = __TIMER + m_pulseTime;
			if(m_isPulseSet)m_onPulse(m_pulses);
			/*if (m_isTrigger && (m_pulses % m_SyncMod) == 0) {
				digitalWrite(m_SyncPin, HIGH);
				m_spstate = true;
			}*/
			if (m_pulses % 6 == 0) {
				//Sixteenth Note
				uint32_t sixteenths = (uint32_t)floor(m_pulses / 6);
				if(m_isStepSet)m_onStep(m_pulses, sixteenths);
				if (sixteenths % 4 == 0) {
					//QuarterNote
					uint32_t quarters = (uint32_t)floor(sixteenths / 4);
					if(m_isBeatSet)m_onBeat(m_pulses, quarters);
				}
			}
			m_pulses++;
			m_beats = (int)floor( m_pulses / 24);
			m_steps = (int)floor(m_pulses / 6);
		}
	}
	if (__TIMER > m_nextPulse - (m_pulseTime / 2)&& m_spstate) {
		digitalWrite(m_SyncPin, LOW);
		m_spstate == false;
	}
}

unsigned unsigned int* BeatClock::getCurrentPulses()
{
	return &m_pulses;
}

unsigned unsigned int* BeatClock::getCurrentSteps()
{
	return &m_steps;
}

unsigned unsigned int* BeatClock::getCurrentBeats()
{
	return &m_beats;
}

void BeatClock::setTempo(int bpm)
{
	m_tempo = bpm;
	m_pulseTime = m_CalculatePulseTime();
}

unsigned int* BeatClock::getTempo()
{
	return &m_tempo;
}

void BeatClock::start()
{
	if (!m_isRunning) {
		m_isRunning = true;
		m_nextPulse = __TIMER + m_pulseTime;
	}
}

void BeatClock::stop()
{
	if (m_isRunning) {
		m_isRunning = false;
	}
}

void BeatClock::reset()
{
	m_pulses = 0;
}

bool BeatClock::isRunning()
{
	return m_isRunning;
}

