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
	 bool m_isRunning = false;
	 unsigned long m_nextStep=0;
	 unsigned long m_millisPerStep=0;
	 unsigned int m_steps=0;
	 unsigned int m_beats=0;
	 unsigned int m_BPM=120;
	 bool m_isStep = false;
	 void m_recalc();
 public:
	BeatClock();
	void tick();
	void setBPM(unsigned int bpm);
	unsigned int getBPM() {return m_BPM;}
	bool isStep() {	return m_isStep; }
	int getSteps() { return m_steps; }
	int getStepsBar() { return m_steps % 16; }
	int getBeats() { return m_beats; }
	int getBeatsBar() { return m_beats = 0; }
	void Start();
	void Stop() { m_isRunning = false; }
	bool isRunning() { return m_isRunning; }


};


#endif

