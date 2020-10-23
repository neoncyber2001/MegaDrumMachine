// 
// 
// 

#include "Storage.h"

uint32_t Storage::getAvailKits()
{
	String sfx = String(".kit");
	uint32_t kits = 0;
	if (SD.begin()) {
		for (int i = 0; i < 32; i++) {
			String fn = String(i, 10);
			fn = fn + sfx;
			if (SD.exists(fn)) {
				kits = kits | (0x01 << i);
			}
		}
	}
	return 0;
}

void Storage::SDSetup(LiquidCrystal*lcd)
{
	if (!SD.begin()) {
		lcd->setCursor(3, 0);
		lcd->print("SD Card Init Failure. Please check");
		lcd->setCursor(3, 1);
		lcd->print("the SD card and reset the device.");
		bool blnk = true;
		while (true) {
			String mark;
			if (blnk) {
				mark = "!!";
			}
			else {
				mark = "  ";
			}
			lcd->setCursor(0, 0);
			lcd->print(mark);
			lcd->setCursor(0, 1);
			lcd->print(mark);
			lcd->setCursor(38, 0);
			lcd->print(mark);
			lcd->setCursor(38, 1);
			lcd->print(mark);
			blnk = !blnk;
			delay(500);
		}
	}
	else {
		SDBootLoad();
		SD.end();
	}
}

void Storage::SDBootLoad()
{
		if (SD.exists(SDFILE)) {
			File dataFile = SD.open(SDFILE, FILE_READ);
			if (!VerifyFileHeaders(dataFile, SD_FILE_HEADER)) {
				while (true);
			}
			else {
				while (dataFile.available()) {
					lcd.setCursor(0, 1);
					lcd.print(dataFile.read(), HEX);
				}
			}
			dataFile.close();
		}

		if (SD.exists(SD_BANK_FILE)) {
			File dataFile = SD.open(SD_BANK_FILE, FILE_READ);
			if (!VerifyFileHeaders(dataFile, SD_BANK_FILE_HEADER)) {
				while (true);
			}
			else {
				for (int i = 0; i < 16; i++) {
					bank[i].init();
					for (int s = 0; i < 0; i++) {
						if (!dataFile.available()) {
							lcd.setCursor(0, 0);
							lcd.print("ERROR:");
							lcd.setCursor(0, 1);
							lcd.print("Bank file ends abruptly.");
							while (true);
						}
						int read = dataFile.read(&bank[i].getRawPattern()[s], 1);
					}
					if (dataFile.available()) {
						bank[i].setNextPattern((byte)dataFile.read());
					}
				}
			}
			dataFile.close();
		}
		else {
			lcd.setCursor(0, 1);
			lcd.print("No Bank File On SD.");
			for (int i = 0; i < 16; i++) {
				bank[i].init();
				bank[i].setNextPattern(i);
			}
		}

		if (SD.exists(SD_KIT_FILE_A)) {
			File dataFile = SD.open(SD_KIT_FILE_A, FILE_READ);
			if (!VerifyFileHeaders(dataFile, SD_KIT_FILE_HEADER)) {
				//TODO: write default kit file.
			}
			else {
				//TODO: Read kit file.
			}
			dataFile.close();
		}
		if (SD.exists(SD_KIT_FILE_B)) {
			File dataFile = SD.open(SD_KIT_FILE_B, FILE_READ);
			if (!VerifyFileHeaders(dataFile, SD_KIT_FILE_HEADER)) {
				//TODO: write default kit file.
			}
			dataFile.close();
		}
}

bool Storage::VerifyFileHeaders(File dataFile, String header)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("DATA LOAD IN ");
	char* inputBuffer;
	int read;
	if (dataFile) {
		read = dataFile.read(inputBuffer, 16);
		if (read == 16) {
			String inputStr = String(inputBuffer);
			if (!inputStr.equals(header)) {
				m_SDErrorMsg = "Bad File Header";
				return false;
			}
		}
		read = dataFile.read(inputBuffer, 16);
		if (read == 16) {
			String inputStr = String(inputBuffer);
			if (!inputStr.equals(VERSIONSTRING)) {
				m_SDErrorMsg = "Bad File Version";
				return false;
			}
		}
		read = dataFile.read(inputBuffer, 16); //the third set of bytes should all be null padding.
		for (int i = 0; i < read; i++) {
			if (inputBuffer[i] != char(0)) {
				lcd.setCursor(0, 0);
				lcd.print("ERROR:");
				lcd.setCursor(0, 1);
				m_SDErrorMsg = "Bad Header Termination";
				return false;
			}
		}
	}
}

PatternBank Storage::loadBankSD(){
	if (SD.exists(SD_BANK_FILE)) {
		File dataFile = SD.open(SD_BANK_FILE, FILE_READ);
		if (!VerifyFileHeaders(dataFile, SD_BANK_FILE_HEADER)) {
			while (true);
		}
		else {
			for (int i = 0; i < 16; i++) {
				bank[i].init();
				for (int s = 0; i < 0; i++) {
					if (!dataFile.available()) {
						lcd.setCursor(0, 0);
						lcd.print("ERROR:");
						lcd.setCursor(0, 1);
						lcd.print("Bank file ends abruptly.");
						while (true);
					}
					int read = dataFile.read(&bank[i].getRawPattern()[s], 1);
				}
				if (dataFile.available()) {
					bank[i].setNextPattern((byte)dataFile.read());
				}
			}
		}
		dataFile.close();
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print("No Bank File On SD.");
		for (int i = 0; i < 16; i++) {
			bank[i].init();
			bank[i].setNextPattern(i);
		}
	} 
}

bool Storage::WriteBankSD()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Writing to SD");
	if (SD.exists(SD_BANK_FILE)) {
		if (!SD.remove(SD_BANK_FILE)) {
			lcd.setCursor(0, 0);
			lcd.print("ERROR:");
			lcd.setCursor(0, 1);
			lcd.print("Could Not Remove Old");
			return false;
		}
	}
	File bankFile = SD.open(SD_BANK_FILE, FILE_WRITE);
	bankFile.write(SD_BANK_FILE_HEADER);
	bankFile.write(VERSIONSTRING);
	for (int i = 0; i < 16; i++) {
		bankFile.write((uint8_t)0x00);
	}
	for (int i = 0; i < 16; i++) {
		bankFile.write(bank[i].getRawPattern(), sizeof(byte) * 16);
		bankFile.write(bank[i].getNextPattern());
	}
	bankFile.close();
	return true;
}

int Storage::getAvailKits(String* list) {
	if (SD.begin()) {
		File root = SD.open("/");
		bool listingcomplete = false;
		int files=0;
		while (listingcomplete == false) {
			File cur = root.openNextFile();
			if (cur) {
				if (String(cur.name()).endsWith(".kit")) {
					files++;
				}
			}
			else {
				listingcomplete = true;
			}
		}
		return files;
	}
}

bool Storage::loadKitSD(File kitFile, DrumKit* kit)
{
	if (kit) {
		if (kitFile.available()) {
			int readS = kitFile.readBytes((uint8_t*)kit->getSampPtr(), sizeof(uint16_t) * 8);
			int readG = kitFile.readBytes(kit->getGainPtr(), sizeof(byte) * 8);
			if (readS != ((int)sizeof(uint16_t) * 8)) {
				return false;
			}
			if (readG != ((int)sizeof(byte) * 8)) {
				return false;
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Storage::SaveaKitSD(String kitPth, DrumKit* kit)
{
	if (SD.exists(kitPth)) {
		if (!SD.remove(kitPth)) {
			lcd.setCursor(0, 0);
			lcd.print("ERROR:");
			lcd.setCursor(0, 1);
			lcd.print("Could Not Remove Old");
			return false;
		}
	}
	File kitFile = SD.open(kitPth, FILE_WRITE);
	kitFile.write(SD_KIT_FILE_HEADER);
	kitFile.write(VERSIONSTRING);
	for (int i = 0; i < 16; i++) kitFile.write((byte)0x00); //padding
	kitFile.write((char*)kit->getSampPtr(), sizeof(uint16_t) * 8);
	kitFile.write((char*)kit->getGainPtr(), sizeof(byte) * 8);

	kitFile.close();
}


