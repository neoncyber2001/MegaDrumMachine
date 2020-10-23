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
	if (m_clock->isRunning()) {
		if (m_clock->isStep()) {
			if ((m_clock->getStepsBar() % 4) == 0) {
				if (m_clock->getStepsBar() == 0) {
					m_wtrig->trackPlayPoly(SYSTK_METRO_A);
				}
				else {
					m_wtrig->trackPlayPoly(SYSTK_METRO_B);
				}
			}
		}
	}
}

void ProgramMode::DrawScreen()
{
	m_lcd->clear();
	m_lcd->setCursor(0, 0);
	m_lcd->print("PROGRAM ");
	
	m_lcd->setCursor(12, 0);
	m_lcd->print("pat:");

	m_lcd->setCursor(20, 0);
	m_lcd->print("nxt:");

	m_lcd->setCursor(26, 0);
	m_lcd->print("ch:");

	m_lcd->setCursor(32, 0);
	m_lcd->print("Step:");
}

void ProgramMode::UpdateScreen()
{
	m_lcd->setCursor(9, 0);
	if (m_isStepSequencing) {
		m_lcd->print("St");
	}
	else {
		m_lcd->print("Ti");
	}

	m_lcd->setCursor(16, 0);
	m_lcd->print(m_patternIndex, BIN);
	m_lcd->print(" ");

	m_lcd->setCursor(24, 0);
	m_lcd->print(m_currentPattern->getNextPattern(),BIN);
	m_lcd->print(" ");

	m_lcd->setCursor(29, 0);
	m_lcd->print(m_selectedChannel, BIN);
	m_lcd->print(" ");

	m_lcd->setCursor(36, 0);
	m_lcd->print(m_clock->getStepsBar(), BIN);
	m_lcd->print(" ");
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
			m_clock->Stop();
			m_isStepSequencing = true;
		}
		else {
			m_clock->Start();
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
		int step = m_clock->getStepsBar();
		for (int i = 0; i < 16; i++) {
			if ((matrix & (0x01 << i)) != 0) {
				m_currentPattern->setTrigger((byte)step, i % 8);
				m_wtrig->trackPlayPoly(m_kit->getSample(i % 8));
			}
		}
	}
	else {
		for (int i = 0; i < 16; i++) {
			if ((matrix & (0x01 << i)) != 0) {
				m_currentPattern->setTrigger((byte)i, m_selectedChannel);
				m_wtrig->trackPlayPoly(m_kit->getSample(m_selectedChannel));
			}
		}
		//TODO:
	}
}
