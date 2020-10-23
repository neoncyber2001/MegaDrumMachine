// Storage.h

#ifndef _STORAGE_h
#define _STORAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include <SD.h>
#include "DrumKit.h"
#include "DrumPattern.h"
#include "PatternBank.h"
#include "LiquidCrystal.h"
#else
	#include "WProgram.h"
#endif

#pragma region SDConstants

#define SDFILE	"DRUMDATA.DAT"
#define SD_FILE_HEADER "AA.M4.DRUM.DATA."

#define SD_BANK_FILE	"PATTERNBANK.DAT"
#define SD_BANK_FILE_HEADER "AA.M4.PATT.BANK."

#define SD_KIT_FILE_A	"KITDATA_0.DAT"
#define SD_KIT_FILE_B	"KITDATA_1.DAT"
#define SD_KIT_FILE_HEADER "AA.M4.SAMPL.KIT."

#pragma endregion


class Storage
{
 protected:
	 String m_SDErrorMsg = "";

 public:
	 uint32_t getAvailKits();
	 bool saveKit(byte kitSlot, DrumKit kit);
	 DrumKit loadKit(byte kitSlot);
	 DrumKit LoadKitFromSD(String kit);
	 PatternBank LoadBankFromSD(String bank);

	 String GetSDError() { return m_SDErrorMsg; };
	 void SDSetup(LiquidCrystal *lcd);
	 void SDBootLoad();
	 bool VerifyFileHeaders(File dataFile, String header);
	 bool WriteBankSD();
	 PatternBank loadBankSD();
	 bool loadKitSD(File kitFile, DrumKit* kit);
	 bool SaveaKitSD(String kitPth, DrumKit* kit);
	 int Storage::getAvailKits(String* list);

};



#endif

