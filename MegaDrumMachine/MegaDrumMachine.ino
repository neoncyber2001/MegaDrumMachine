/*
 Name:		MegaDrumMachine.ino
 Created:	8/5/2020 2:14:55 PM
 Author:	djneo
*/

// the setup function runs once when you press reset or power the board
/*
File Version Strings
76rGd0wA58LHXdVb <-- Current
y28ytsSUCD5mfITW
bVAG4LFQ4IO6SSxt
beektTkAiMZlnRNk
YPn1l4HV40VTVUkK
KWyQfYeBHb4jbitE
Rq0k58rD3wxcETBH
qHtd4ciUECfs64qE
SWD5rvANIJWBlVL6
ZeAXOLy5nh0wNL19

*/
#define VERSIONSTRING	"76rGd0wA58LHXdVb"

#include <SPI.h>
#include "LCDWidget.h"
#include "LCDView.h"
#include "LCDWidgets.h"
#include "LCDWidgets.h"
#include <RotaryEncoder.h>
#include <LiquidCrystal.h>
#include <string.h>
#include "ValueControl.h"
#include "DrumKit.h"
#include <Arduino.h>
#include <Bounce2.h>
#include "ButtonReader.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <wavTrigger.h>
#include "BeatClock.h"
#include "Sequencer.h"
#include "PatternBank.h"
#include "DrumPattern.h"

#ifdef __SAMD51__ 
	#include <SD.h>
	#define SDFILE	"DRUMDATA.DAT"
	#define SD_FILE_HEADER "AA.M4.DRUM.DATA."

	#define SD_BANK_FILE	"PATTERNBANK.DAT"
	#define SD_BANK_FILE_HEADER "AA.M4.PATT.BANK."

	#define SD_KIT_FILE_A	"KITDATA_0.DAT"
	#define SD_KIT_FILE_B	"KITDATA_1.DAT"
	#define SD_KIT_FILE_HEADER "AA.M4.SAMPL.KIT."

#else
	#include <EEPROM.h>
#endif // 


//#define WTSerial	Serial
//RotaryEncoder encoder(21, 20);
DrumKit CurrentKit;

#define UPDATE_PERIOD	250


unsigned long NextValues=0;
#define BTN_INPUT_START		36
#ifndef __SAMD51__
	#define EPOFFSET		0x02
#endif
bool isAltBoot = false;
ButtonReader reader;
LiquidCrystal_I2C lcd(0x27, 40, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
BeatClock clk;
Sequencer seq;
DrumPattern bank[16];
byte DrumPatternIndex=0;
byte DrumPatternNext=0;
byte CurrentInsSlot = 0;
byte displayMode = 0;
bool NavMode = true;
byte prevIndex = 0;
byte itemIndex = 0;
byte itemMax = 4;
bool ProgramMode = 0;
bool UpdateUI = false;
bool RedrawUI = false;
int* temporary = 0;
wavTrigger wTrig;
int gRateOffset = 0;
bool isMetronomeRunning = false;

#define SYSTK_METRO_A	1
#define SYSTK_METRO_B	2


#define MODE_PLAY	0x00
#define MODE_PROG	0x01
#define MODE_KIT	0x02
#define MODE_PSTOR  0x03
#define MODE_KSTOR	0x04

#ifdef __SAMD51__

#endif // 


#pragma region encoder


#pragma endregion

void setup() {
	Serial.begin(9600);
	reader.begin(true);
	//DrumTriggerButtons
	for (int i = 0; i < 16; i++) {
		pinMode(37 + i, INPUT_PULLUP);
	}
	lcd.init();                      // initialize the lcd 
//	lcd.init(); 
	lcd.noAutoscroll();
	lcd.noBlink();
	lcd.noCursor();  
	lcd.backlight();
	lcd.clear();
	lcd.setCursor(0, 0);
	
#ifdef __SAMD51__
	if (!SD.begin()) {
		lcd.setCursor(3, 0);
		lcd.print("SD Card Init Failure. Please check");
		lcd.setCursor(3, 1);
		lcd.print("the SD card and reset the device.");
		bool blnk = true;
		while (true) {
			String mark;
			if (blnk) {
				mark = "!!";
			}
			else {
				mark = "  ";
			}
			lcd.setCursor(0, 0);
			lcd.print(mark);
			lcd.setCursor(0, 1);
			lcd.print(mark);
			lcd.setCursor(38, 0);
			lcd.print(mark);
			lcd.setCursor(38, 1);
			lcd.print(mark);
			blnk = !blnk;
			delay(500);
		}
	}
	else {
		SDBootLoad();
	}
#else
	eepromBootLoad();
#endif
	/*

	*/
	delay(500);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Checking for boot mod buttons...");
	for (int i = 0; i < 20; i++) {
		lcd.setCursor(0, 1);
		lcd.print(20 - i, DEC);
		lcd.setCursor(8, 1);
		reader.doScan();
		lcd.print(reader.getButtonsDown(), HEX);
		delay(100);
	}
	reader.doScan();
	if (reader.isButtonDown(0)) {
		isAltBoot = true;
	}
	lcd.clear();
	lcd.setCursor(16,0);
	lcd.print("DR-2650");
	lcd.setCursor(7,1);
	lcd.print("WAV TRIGGER - DRUM MACHINE");
	delay(1000);
	wTrig.start();
	delay(10);  
	wTrig.stopAllTracks();
	wTrig.samplerateOffset(0);
	clk.init(true, false, false);
	seq.init(&clk, &bank[0], onTrigger,bank);
	clk.setOnStep(onStep);
	clk.setOnBeat(onBeat);
	setDisplayMode(0,1);
}

#ifdef __SAMD51__
void SDBootLoad() {
	if (SD.exists(SDFILE)) {
		File dataFile = SD.open(SDFILE, FILE_READ);
		if (!VerifyFileHeaders(dataFile, SD_FILE_HEADER)) {
			while(true);
		}
		else {
			while (dataFile.available()) {
				lcd.setCursor(0,1);
				lcd.print(dataFile.read(),HEX);
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

bool VerifyFileHeaders(File dataFile, String header) {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("DATA LOAD IN ");
	char* inputBuffer;
	int read;
	if (dataFile) {
		read = dataFile.read(inputBuffer, 16);
		if (read == 16) {
			String inputStr = String(inputBuffer);
			if (!inputStr.equals(SD_FILE_HEADER)) {
				lcd.setCursor(0, 0);
				lcd.print("ERROR:");
				lcd.setCursor(0, 1);
				lcd.print("Bad file header");
				return false;
			}
		}
		read = dataFile.read(inputBuffer, 16);
		if (read == 16) {
			String inputStr = String(inputBuffer);
			if (!inputStr.equals(VERSIONSTRING)) {
				lcd.setCursor(0, 0);
				lcd.print("ERROR:");
				lcd.setCursor(0, 1);
				lcd.print("Bad File Version");
				//TODO File Does Not Match Version.
				return false;
			}
		}
		read = dataFile.read(inputBuffer, 16); //the third set of bytes should all be null padding.
		for (int i = 0; i < read; i++) {
			if (inputBuffer[i] != char(0)) {
				lcd.setCursor(0, 0);
				lcd.print("ERROR:");
				lcd.setCursor(0, 1);
				lcd.print("Bad Header Term");
				return false;
			}
		}
	}
}


bool WriteBankSD() {
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
		bankFile.write(bank[i].getRawPattern(), sizeof(byte)*16);
		bankFile.write(bank[i].getNextPattern());
	}
	bankFile.close();
	return true;
}


bool LoadKitSD(File kitFile, DrumKit* kit) {
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

bool SaveKitSD(String kitPth, DrumKit* kit) {
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

#endif

void onBeat(uint32_t pulses, uint32_t beats) {
	if (isMetronomeRunning) {
		if (beats % 4 == 0) {
			wTrig.trackPlayPoly(SYSTK_METRO_A);
		}
		else {

			wTrig.trackPlayPoly(SYSTK_METRO_B);
		}
	}
}

#ifndef __SAMD51__
boolean chkEEPROM() {
	byte valueA = EEPROM.read(0x00);
	byte valueB = EEPROM.read(0x01);
	if ((char)valueA == 'D' && (char)valueB == 'P') {
		return true;
	}
	else {
		return false;
	}
}

void  eepromBootLoad() {
	lcd.print("Checking EEPROM... ");
	if (chkEEPROM) {
		for (int i = 0; i < 16; i++) {
			for (int s = 0; s < 16; s++) {
				bank[i].init();
				bank[i].getRawPattern()[s] = EEPROM.read((i * 16 + s) + EPOFFSET);
			}
		}
		lcd.setCursor(0, 1);
		lcd.print("Loaded");
	}
	else {
		EEPROM.write(0x00, 'D');
		EEPROM.write(0x01, 'P');
		for (int i = 0; i < 16; i++) {
			for (int s = 0; s < 16; s++) {
				EEPROM.write((i * 16 + s) + EPOFFSET, 0x00);
			}
		}
		lcd.setCursor(0, 1);
		lcd.print("Initialized");
	}
}
#endif
void onStep(uint32_t pulse, uint32_t steps) {
	UpdateUI = true;	
}


void onTrigger(byte trigger) {
	for (byte i = 0; i < 8; i++) {
		byte act = trigger & (0x01 << i);
		if (act > 0) {
			/*switch (i) {
			case 0:
				wTrig.trackPlayPoly(CurrentKit.getKick());
				break;
			case 1:
				wTrig.trackPlayPoly(CurrentKit.getKick());
				break;
			case 0:
				wTrig.trackPlayPoly(CurrentKit.getKick());
				break;
			case 0:
				wTrig.trackPlayPoly(CurrentKit.getKick());
				break;
			case 0:
				wTrig.trackPlayPoly(CurrentKit.getKick());
				break;
			case 0:
				wTrig.trackPlayPoly(CurrentKit.getKick());
				break;
			}
			*/
		}
	}
}

byte dsp = 0;

void setDisplayMode(byte mode, byte items) {
	displayMode = mode;
	itemIndex = 0;
	NavMode = true;
	itemMax = items;
	UpdateUI = true;
	RedrawUI = true;
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (isAltBoot) {
		//Todo
	}
	else {
		checkMode(displayMode);
	}
	reader.readRBtn();
	//int btn = //analogRead(RBTN_PIN);

#pragma region Static Mode Change and Function Buttons
	//These buttons always perform the same function 
	// nomatter what the display mode is.
	if (reader.getRBtnPressed() == 0) {
		if (displayMode != MODE_PLAY) {
			setDisplayMode(MODE_PLAY,3);
		}
	}
	else if (reader.getRBtnPressed() == 1) {
		if (displayMode != MODE_PROG) {
			setDisplayMode(MODE_PROG, 4);
		}
	}
	else if (reader.getRBtnPressed() == 5) {
		isMetronomeRunning = !isMetronomeRunning;
		UpdateUI = true;
	}
	else if (reader.getRBtnPressed() == 6) {
		if (NavMode) {
			if (itemIndex > 0) {
				itemIndex--;
				UpdateUI = true;
			}
		}
		else {
			//todo
		}
	}
	else if (reader.getRBtnPressed() == 7) {
		NavMode = !NavMode;
		if (!NavMode) {
			swapIn(itemIndex);
			
		}
		else {
			swapOut(itemIndex);
		}
		UpdateUI = true;
	}
	else if (reader.getRBtnPressed() == 8) {
		if (NavMode) {
			if (itemIndex < itemMax) {
				itemIndex++;
				UpdateUI = true;
			}
		}
		else {
			//todo
		}

	}	
	else if (reader.getRBtnPressed() == 9) {
		if (!clk.isRunning()) {
			clk.reset();
			UpdateUI = true;
		}
	}
	else if (reader.getRBtnPressed() == 10) {
		if (!clk.isRunning()) {
			clk.start();
		}
		else {
			clk.stop();
		}
		UpdateUI = true;
	}

	if (reader.haveBtnsChanged()) {
		if (displayMode == MODE_PLAY) doModeBtns();
	}
#pragma endregion
}


void doModeBtns() {
	uint16_t btn = reader.getButtonsPressed();
	
	for (int i = 0; i < 16; i++) {
		if ((btn & (0x0001 << i)) > 0) {
			DrumPatternNext = i;
		}
	}
}

void chkModeBtns(byte mode) {
	int rbtn = reader.getRBtnPressed();
	if (rbtn != -1) {
		switch (mode) {
		case MODE_PLAY:
			break;
		case MODE_PROG:
			break;
		case MODE_KIT:
			break;
		case MODE_KSTOR:
			break;
		case MODE_PSTOR:
			break;
		default:
			break;
		}
	}
}


void checkMode(byte mode) {
	clk.tick();
	switch (mode) {
	case MODE_PLAY:
		if (RedrawUI) { 
			PlayMenuDraw();
			RedrawUI = false;
		}
		if (UpdateUI) {
			PlayMenuUpdate();
			UpdateUI = false;
		}
		break;	
	case MODE_PROG:
		if (RedrawUI) {
			ProgramMenuDraw();
			RedrawUI = false;
		}
		if (UpdateUI) {
			ProgramMenuUpdate();
			UpdateUI = false;
		}
		break;
	default:
		//nothing
		break;
	};
}
bool firstScreen = true;
void PlayMenuDraw() {
	lcd.clear();
	lcd.flush();
	lcd.noAutoscroll();
	lcd.setCursor(0, 0);
	lcd.print("<Play>");

	lcd.setCursor(10, 0);
	lcd.print("BPM:");

	lcd.setCursor(20, 0);
	lcd.print("Pat:");

	lcd.setCursor(30, 0);
	lcd.print("Next:");

	lcd.setCursor(0, 1);
	lcd.print("BEAT:");
	lcd.setCursor(21, 1);
	lcd.print("BAR:");
	lcd.setCursor(38, 1);
	lcd.print((char)0xE0);
}
void PlayMenuUpdate(){
	lcd.setCursor(14, 0);
	lcd.print(clk.getTempo(), DEC);
	if (itemIndex == 0)lcd.print("#");
	lcd.print("  ");
	lcd.setCursor(24, 0);
	lcd.print(DrumPatternIndex, DEC);
	if (itemIndex == 1)lcd.print("#");
	lcd.print(" ");
	lcd.setCursor(35, 0);
	lcd.print(DrumPatternNext, DEC);
	if (itemIndex == 2)lcd.print("#");
	lcd.print(" ");
	lcd.setCursor(5, 1);
	for (int i = 0; i < 16; i++) {
		if (i <= (clk.getCurrentSteps()%16)) {
			if (i % 4 == 0) {
				lcd.print((char)0xDB);
			}
			else {
				lcd.print((char)0xA5);
			}
		}
		else {
			lcd.print(" ");
		}
	}
	lcd.setCursor(25, 1);
	lcd.print(((int)floor(clk.getCurrentBeats() / 4)),DEC);
	lcd.setCursor(39, 1);
	if (clk.isRunning()) {
		lcd.print(">");
	}
	else { 
		lcd.print((char)0xDB); 
	}

	lcd.setCursor(39, 0);
	if (isMetronomeRunning) {
		lcd.print("!");
	}
	else {
		lcd.print(" ");
	}
	
}
#pragma endregion


void ProgramMenuDraw() {
	lcd.clear();
	lcd.flush();
	lcd.noAutoscroll();
	lcd.setCursor(0, 0);
	lcd.print("<Program>");

	lcd.setCursor(10, 0);
	lcd.print("BPM:");

	lcd.setCursor(20, 0);
	lcd.print("PAT:");

	lcd.setCursor(30, 0);
	lcd.print("NEXT:");
	if (!ProgramMode) {
		lcd.setCursor(0, 1);
		lcd.print("S[");
		lcd.setCursor(10, 1);
		lcd.print("]");
		lcd.setCursor(25, 1);
		lcd.print("STEP:");
	}
	else {
		lcd.setCursor(0, 1);
		lcd.print("D[");
		lcd.setCursor(10, 1);
		lcd.print("]");
		lcd.setCursor(25, 1);
		lcd.print("DRUM:");

	}
	lcd.setCursor(37, 1);
	lcd.print((char)0xE0);

}
void ProgramMenuUpdate() {
	lcd.setCursor(14, 0);
	lcd.print(clk.getTempo(), DEC);
	if (itemIndex == 0) {
		lcd.print("* ");
	}
	else {
		lcd.print("  ");
	}
	lcd.setCursor(24, 0);
	lcd.print(DrumPatternIndex, DEC);
	if (itemIndex == 1) {
		lcd.print("* ");
	}
	else {
		lcd.print("  ");
	}
	lcd.setCursor(35, 0);
	lcd.print(DrumPatternIndex, DEC);
	if (itemIndex == 2) {
		lcd.print("* ");
	}
	else {
		lcd.print("  ");
	}
	lcd.setCursor(30, 3);
	lcd.print((clk.getCurrentSteps()%16), DEC);
	if (itemIndex == 3) {
		lcd.print("* ");
	}
	else {
		lcd.print("  ");
	}

	lcd.setCursor(39, 0);
	if (isMetronomeRunning) {
		lcd.print("!");
	}
	else {
		lcd.print(" ");
	}
}

void serialEvent() {
	while (Serial.available()) {
		int b = Serial.read();
		if (b == '0') {
			//itemIndex = 0;
		}
		else if (b == '1') {
			//itemIndex = 1;
		}

		else if (b == '2') {
			//itemIndex = 2;
		}

		else if (b == '3') {
			//itemIndex = 3;
		}
		Serial.print(b, HEX);
	}
	Serial.println(" Input OK!");
}

void swapIn(int item) {
	if (displayMode == MODE_PLAY) {
		switch (item) {
		case 0:
			*temporary = clk.getTempo();
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}
	}
	else if (displayMode == MODE_PROG) {

	}
}

void swapOut(int item) {

}

void processAdd(int item) {

}
void processSubtract(int item) {

}

void altBootLoop() {
	while(true){

	}
}