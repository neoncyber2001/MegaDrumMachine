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

#include "Storage.h"
#include "ProgramMode.h"
#include "ScreenMode.h"
#define VERSIONSTRING "76rGd0wA58LHXdVb"

#include <SPI.h>
#include <RotaryEncoder.h>
#include <LiquidCrystal.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <wavTrigger.h>
#include <Arduino.h>
#include <Bounce2.h>


#include "DrumKit.h"
#include "BeatClock.h"
#include "Sequencer.h"
#include "PatternBank.h"


#include "ButtonReader.h"
#include "BtnPad.h"
#include "DMPins.h"


byte metroChar[] = {
  0x00,
  0x00,
  0x0E,
  0x15,
  0x17,
  0x11,
  0x0E,
  0x00
};

#define BTNCT	7
Bounce* buttons = new Bounce[BTNCT];
int btnPins[BTNCT] = { 24, 25, 26, 27, 29, 31, 28 };

#define SYSTK_METRO_A	1
#define SYSTK_METRO_B	2
wavTrigger wTrig;

ButtonReader reader = ButtonReader();
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x14, 40, 02);
PatternBank bank;
DrumKit kit;
BeatClock clock;

ScreenMode* Modes = { new ProgramMode(&bank, &kit, &clock, &wTrig, (LiquidCrystal*)&lcd) };

void initWaveTrigger() {
	 wTrig.start();
	 delay(10);
	 wTrig.stopAllTracks();
	 wTrig.samplerateOffset(0);
 }

 void CheckMode() {
	 bool playSw = digitalRead(PIN_MODETOG_A);
	 bool kitSw = digitalRead(PIN_MODETOG_B);
}


 
 
 void setup() {
	Serial.begin(9600);
	reader.begin(true);
	for (int i = 0; i < BTNCT; i++) {
		buttons[i].attach(btnPins[i], INPUT);
	}

	//LCD Setup
	lcd.init();                      // initialize the lcd 
	lcd.noAutoscroll();
	lcd.noBlink();
	lcd.noCursor();  
	lcd.backlight();
	lcd.createChar(0, metroChar);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.clear();

	//PlayView.begin(2, 40, String("Play"), 4, playWidgets, &lcd);
}

void loop() {
	lcd.setCursor(0, 0);
	for (int i = 0; i < BTNCT; i++) {
		buttons[i].update();
		lcd.print(buttons[i].read());
	}
}
