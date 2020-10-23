// ScreenMode.h

#ifndef _SCREENMODE_h
#define _SCREENMODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <LiquidCrystal.h>
#else
	#include "WProgram.h"
#endif

enum ScreenCommand :byte {
	/// <summary>
	/// No command issued
	/// </summary>
	SCMD_NONE=0x00,

	/// <summary>
	/// Transport button (play/stop) is pressed (red button on prototype box)
	/// </summary>
	SCMD_TPortButton_Pressed,
	
	/// <summary>
	/// Metronome Button is pressed.
	/// </summary>
	SCMD_MetroBtn_Pressed,
	
	/// <summary>
	/// Storage Button is pressed
	/// </summary>
	SCMD_StorageBtn_Pressed,
	
	/// <summary>
	/// Action Button is pressed,
	/// </summary>
	SCMD_ActionBtn_Pressed,
	
	/// <summary>
	/// Encoder rotated to decrement a value.
	/// </summary>
	SCMD_JogIncrement,
	
	/// <summary>
	/// Encoder rotated to increment a value.
	/// </summary>
	SCMD_JogDecrement,
	
	/// <summary>
	/// Encoder Clicked
	/// </summary>
	SCMD_JogButton_Pressed,		
	

//	CMD_MatrixInput_Recieved	
};

class ScreenMode
{
 protected:
	 LiquidCrystal* m_lcd;

 public:
	 /// <summary>
	 /// base constructor.
	 /// </summary>
	 /// <param name="lcd"></param>
	 ScreenMode(LiquidCrystal* lcd) {
		 m_lcd = lcd;
	 }

	 /// <summary>
	 /// perform logic update (should be called once per loop when mode is active).
	 /// </summary>
	 virtual void Tick() = 0;

	 /// <summary>
	 /// Clear and draw display;
	 /// </summary>
	 virtual void DrawScreen() = 0;

	 /// <summary>
	 /// Request minimal display update.
	 /// </summary>
	 /// <param name="lcd"></param>
	 virtual void UpdateScreen() = 0;
	 
	 /// <summary>
	 /// Indicate that the user has pressed one of the command buttons or has manipulated the rotary encoder. (The mode switch is not included.)
	 /// </summary>
	 /// <param name="cmd"></param>
	 virtual void IssueCommand(ScreenCommand cmd) = 0;
	 
	 /// <summary>
	 /// Any of the 16 button matrix inputs for note/step programming and pattern selection.
	 /// NOTE* Use this command with uint16_t parameter overload.
	 /// The parameter is a set of byte flags indicating which buttons have been pressed with the most signifigant bit representing the first button of the first row.
	 /// For example, a value of 0x8080 (binary: 1000 0000 1000 0000) represents the first and ninth buttons pressed.
	 /// </summary>
	 virtual void MatrixInput(uint16_t matrix) = 0;
};


#endif

