// 
// 
// 

#include "ProgramMode.h"

ProgramMode::ProgramMode(PatternBank* bank, DrumKit* kit, BeatClock* clock, wavTrigger* wtrig, LiquidCrystal* lcd):ScreenMode(lcd)
{
	m_bank = bank;
	m_kit = kit;
	m_clock = clock;
	m_wtrig = wtrig;
	m_currentPattern = m_bank->getPatternPtr(m_patternIndex);
}

void ProgramMode::Tick()
{
}

void ProgramMode::DrawScreen()
{
	m_lcd->clear();
	m_lcd->setCursor(0, 0);
	m_lcd->print("PROGRAM ");
	m_lcd->setCursor(9, 0);
	m_lcd->print("M");
	m_lcd->
}

void ProgramMode::UpdateScreen()
{
}

void ProgramMode::IssueCommand(ScreenCommand cmd)
{
	switch (cmd) {
	case SCMD_NONE:
		//Do nothing
		break;
	case SCMD_JogIncrement:
		if (m_selectedChannel < 8) {
			m_selectedChannel++;
		}
		break;
	case SCMD_JogDecrement:
		if (m_selectedChannel > 0) {
			m_selectedChannel--;
		}
		break;
	case SCMD_TPortButton_Pressed:
		if (m_clock->isRunning()) {
			m_clock->stop();
			m_isStepSequencing = true;
		}
		else {
			m_clock->start();
			m_isStepSequencing = false;
		}
		break;
	case SCMD_StorageBtn_Pressed:
		//todo Temp switch to BankStorage mode.
		break;
	default:
		//ignore
	}
}

void ProgramMode::MatrixInput(uint16_t matrix)
{
	if (!m_isStepSequencing) {
		int step = *m_clock->getCurrentSteps() % 16;
		for (int i = 0; i < 16; i++) {
			if ((matrix & (0x01 << i)) != 0) {
				m_currentPattern->setTrigger((byte)step, i % 8);
			}
		}
	}
	else {
		//TODO:
	}
}
