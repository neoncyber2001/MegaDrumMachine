#ifndef _LCDWidget_h
#define _LCDWidget_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "LCDWidgets.h"
using namespace LCDWidgets;
	template <class T> class LCDWidget {
	public:
		String getTitle();
		void setTitle(String title);
		void bindVariable(T* var);
	private:
		String m_title;

	};


#endif

