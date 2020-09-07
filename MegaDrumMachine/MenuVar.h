// MenuVar.h

#ifndef _MENUVAR_h
#define _MENUVAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>

template <class T>
class MenuVar
{

 public:
	virtual void init(char*displayName, T*boundVar, int itemIndex);
	virtual void constrainValue(T lbound, T ubound);
	virtual void beginEdit();
	virtual void endEdit();
	virtual void IncreaseValue(int incBy = 1);
	virtual void DecreaseValue(int decBy = 1);
	virtual void resync();
	virtual T* getBoundVar() { return m_boundVar; }
	virtual void setBoundVar(T* var) { m_boundVar = var; }
	virtual bool isEditing();
	virtual void displaySelf(LiquidCrystal_I2C* display, int iIndex);
	
	

protected:
	char* m_displayname;
	T* m_boundVar;
	T m_scratchVar;
	bool m_constrainValue;
	T m_max;
	T m_min;
	bool m_isEditing = false;;
	int m_itemIndex;

};

/*

class MenuVar
{
 protected:
	 char* m_displayname;
	 int* m_boundVar;
	 int m_scratchVar;
	 bool m_constrainValue;
	 int m_max;
	 int m_min;
	 bool m_isEditing = false;;
	 int m_itemIndex;

 public:
	virtual void init(char*displayName, int*boundVar, int itemIndex);
	virtual void init(char* displayName, int* boundVar, int itemIndex, int min, int max);
	virtual void beginEdit();
	virtual void endEdit();
	virtual void IncreaseValue(int incBy = 1);
	virtual void DecreaseValue(int decBy = 1);
	virtual void resync();
	virtual int* getBoundVar() { return m_boundVar; }
	virtual void setBoundVar(int* var) { m_boundVar = var; }
	virtual bool isEditing();
	void displaySelf(LiquidCrystal_I2C* display, int iIndex);
};
*/


#endif

