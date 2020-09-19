// 
// 
// 

#include "Sequencer.h"


void Sequencer::init(BeatClock* bclock, DrumPattern* pat, onTrigFn triggerFn, DrumPattern* patternbank)
{
	m_clock = bclock;
	m_pattern = pat;
	m_onTrig = triggerFn;
	m_isOnTrigSet=true;
	m_sequencerMode = SEQ_PLAY;
	m_recStep = 0;
	m_isQueued = false;
	m_queuedPattern = nullptr;
	m_isInitialized = true;
	m_bnk = patternbank;
}

void Sequencer::setSeqMode(bool mode)
{
	m_sequencerMode = mode;
}

bool Sequencer::getSeqMode()
{
	return m_sequencerMode;
}

void Sequencer::nextStepR()
{
	if (m_sequencerMode == SEQ_RECORD) {
		if (m_recStep < 15)m_recStep++;
	}
}

void Sequencer::prevStepR()
{
	if (m_sequencerMode == SEQ_RECORD) {
		if (m_recStep > 0)m_recStep--;
	}
}

int Sequencer::getCurrentStepNoR()
{
	if (m_sequencerMode == SEQ_RECORD) {
		return m_recStep;
	}
	else {
		return -1;
	}
}

void Sequencer::toggleSampleR(uint8_t samp_no)
{
	m_pattern->setTrigger(m_recStep, samp_no);
}

uint8_t Sequencer::getCurrentStep()
{
	if (m_sequencerMode == SEQ_RECORD) {
		return m_pattern->getStep(m_recStep);
	}
	else {
		return (m_clock->getCurrentSteps() % 16);
	}
}

void Sequencer::setNextPattern(DrumPattern* dp)
{
	if (m_sequencerMode == SEQ_PLAY) {
		if (m_clock->isRunning()) {
			m_queuedPattern = dp;
			m_isQueued = true;
		}
		else {
			m_pattern = dp;
			m_isQueued = false;
			m_clock->reset();
		}
	}
	else {
		m_pattern = dp;
		m_recStep = 0;
	}
}

void Sequencer::onStep(uint32_t pulses, uint32_t steps)
{
	if (m_isQueued && (steps%16)==0) {
		m_pattern = m_queuedPattern;
		setNextPattern(&m_bnk[m_pattern->getNextPattern()]);
	}
	if (m_isOnTrigSet) {
		m_onTrig(m_pattern->getStep(steps % 16));
	}
}
