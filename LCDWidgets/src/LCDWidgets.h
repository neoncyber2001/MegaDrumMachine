/*
 Name:		LCDWidgets.h
 Created:	9/4/2020 7:07:39 PM
 Author:	djneo
 Editor:	http://www.visualmicro.com
*/

#ifndef _LCDWidgets_h
#define _LCDWidgets_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

namespace LCDWidgets {

#include "LCDWidget.h"


}

#endif

