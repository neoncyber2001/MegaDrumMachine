// BeatClock.h

#ifndef _BEATCLOCK_h
#define _BEATCLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define __BEATTIME (1000/(m_tempo/60))
#define __TIMER micros()

typedef void (*onPulseFn)(uint32_t);			//void onPulse(uint32_t pulses){...}
typedef void (*onStepFn)(uint32_t, uint32_t);	//void onStep(uint32_t pulses, uint32_t steps){...}
typedef void (*onBeatFn)(uint32_t, uint32_t);	//void onStep(uint32_t pulses, uint32_t beats){...}

#ifndef CLOCK_TRIGGER_PIN
#define CLOCK_TRIGGER_PIN	LED_BUILTIN
#endif // !CLOCK_TRIGGER_PIN
/// <summary>
/// Keeps timing (or is supposed to)
/// </summary>
class BeatClock
{
 protected:
	 
	 bool m_spstate = 0;
	 byte m_SyncPin=0;
	 byte m_SyncMod = 1;
	 bool m_isClockMaster;
	 bool m_isTrigger;
	 bool m_isUartMidi;
	 bool m_isPulseSet;
	 bool m_isStepSet;
	 bool m_isBeatSet;
	 unsigned int m_pulses;
	 onPulseFn m_onPulse;
	 onStepFn m_onStep;
	 onBeatFn m_onBeat;
	 unsigned int m_tempo; //in bpm
	 unsigned int m_ppqn=24; //Pulses Per Quarter Note
	 bool m_isRunning;
	 unsigned int m_beats;
	 unsigned int m_steps;
	 unsigned long m_nextPulse;
	 unsigned long m_pulseTime;
	 unsigned long m_CalculatePulseTime();
 public:
	BeatClock();
	void init();
	void init(bool master, bool midi, bool trigger);
	void setOnPulse(onPulseFn userFn);
	void setOnStep(onStepFn userFn);
	void setOnBeat(onBeatFn userFn);
	void tick();
	unsigned int* getCurrentPulses();
	unsigned int* getCurrentSteps();
	unsigned int* getCurrentBeats();
	void setTempo(int bpm);
	unsigned int* getTempo();
	//void setPPQN(int pulses);
	//int getPPQN();
	void start();
	void stop();
	void reset();
	bool isRunning();
	int* getTempoPtr() { return &m_tempo; }
	int* getPulsePtr() { return &m_pulses; }
	int* getBeatPtr() { return &m_beats; }
	int* getStepsPtr() { return &m_steps; }
	bool* getRunningPtr() { return &m_isRunning; }

};


#endif

