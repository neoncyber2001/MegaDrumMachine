// Sequencer.h

#ifndef _SEQUENCER_h
#define _SEQUENCER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "BeatClock.h"
#include "DrumPattern.h"

typedef void(*onTrigFn)(uint8_t);

#define SEQ_RECORD		0
#define SEQ_PLAY		1

class Sequencer
{
 protected:
	 bool m_isInitialized=false;
	 bool m_sequencerMode;
	 int m_recStep;
	 BeatClock* m_clock;
	 DrumPattern* m_pattern;
	 bool m_isQueued;
	 DrumPattern* m_queuedPattern;
	 bool m_isOnTrigSet;
	 onTrigFn m_onTrig;
	 DrumPattern* m_bnk;
 public:
	void init(BeatClock* bclock, DrumPattern* pat, onTrigFn triggerFn, DrumPattern* patternbank);
	void setSeqMode(bool mode);
	bool getSeqMode();
	void nextStepR();
	void prevStepR();
	int getCurrentStepNoR();
	void toggleSampleR(uint8_t samp_no);
	uint8_t getCurrentStep();
	DrumPattern* getCurrentPattern() { return m_pattern; };
	void setNextPattern(DrumPattern* dp);
	void onStep(uint32_t pulses, uint32_t steps);
};

#endif

