// ProgramMode.h

#ifndef _PROGRAMMODE_h
#define _PROGRAMMODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "ScreenMode.h"
	#include <LiquidCrystal.h>
#include "DrumPattern.h"
#include "PatternBank.h"
#include "DrumKit.h"
#include "BeatClock.h"
#include <wavTrigger.h>

#else
	#include "WProgram.h"
#endif


class ProgramMode:public ScreenMode
{
 protected:
	 bool m_isStepSequencing = false;	//false = Track Sequencing | true = Step Sequencing
	 byte m_patternIndex = 0;
	 PatternBank* m_bank;
	 DrumPattern* m_currentPattern;
	 DrumKit* m_kit;
	 BeatClock* m_clock;
	 wavTrigger* m_wtrig;
	 byte m_selectedChannel = 0;


 public:
	 ProgramMode(PatternBank* bank, DrumKit* kit, BeatClock* clock, wavTrigger* wtrig, LiquidCrystal* lcd);

	 // Inherited via ScreenMode
	 virtual void Tick() override;
	 virtual void DrawScreen() override;
	 virtual void UpdateScreen() override;
	 virtual void IssueCommand(ScreenCommand cmd) override;
	 virtual void MatrixInput(uint16_t matrix) override;
};



#endif

