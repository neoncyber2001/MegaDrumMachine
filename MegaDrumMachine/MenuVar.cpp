// 
// 
// 

#include "MenuVar.h"
template<class T>
void MenuVar<T>::init(char* displayName, T* boundVar, int itemIndex)
{
	m_displayname = displayName;
	m_boundVar = boundVar;
	m_itemIndex = itemIndex;
	m_constrainValue = false;
}

template<class T>
void MenuVar<T>::constrainValue(T lbound, T ubound)
{
	m_constrainValue = true;
	m_max = ubound;
	m_min = lbound;
}

template<class T>
void MenuVar<T>::beginEdit()
{
	if (!m_isEditing) {
		m_scratchVar = *m_boundVar;
		m_isEditing = true;
	}

}

template<class T>
void MenuVar<T>::endEdit()
{
	if (m_isEditing) {
		*m_boundVar = m_scratchVar;
		m_isEditing = false;
	}
}

template<class T>
void MenuVar<T>::IncreaseValue(int incBy)
{
	if (isEditing) {
		if (m_constrainValue) {
			if (m_scratchVar < m_max) {
				m_scratchVar+= incBy;
			}
		}
		else{
			m_scratchVar+= incBy;
		}
	}
}

template<class T>
void MenuVar<T>::DecreaseValue(int decBy)
{
	if (isEditing) {
		if (m_constrainValue) {
			if (m_scratchVar > m_min) {
				m_scratchVar-= decBy;
			}
		}
		else {
			m_scratchVar-= decBy;
		}
	}
}

template<class T>
void MenuVar<T>::resync()
{
	m_scratchVar = *m_boundVar;
}

template<class T>
bool MenuVar<T>::isEditing()
{
	return m_isEditing;
}


template<class T>
void MenuVar<T>::displaySelf(LiquidCrystal_I2C* display, int iIndex)
{
	display->print(m_displayname);
	display->print(":");
	if (m_isEditing) {
		display->print(m_scratchVar);
	}
	else {

		display->print(*m_boundVar);
	}
	if (iIndex == m_itemIndex) {
		display->print("#");
	}
	else {
		display->print(" ");
	}
}




/* backup

void MenuVar<class T>::init(char* displayName, int* boundVar, int itemIndex)
{
	m_displayname = displayName;
	m_boundVar = boundVar;
	m_itemIndex = itemIndex;
	m_constrainValue = false;
}

void MenuVar<class T>::init(char* displayName, int* boundVar, int itemIndex, int min, int max)
{
	m_displayname = displayName;
	m_boundVar = boundVar;
	m_itemIndex = itemIndex;
	m_constrainValue = true;
	m_min = min;
	m_max = max;

	m_scratchVar = *m_boundVar;
}

void MenuVar<class T>::beginEdit()
{
	if (!m_isEditing) {
		m_scratchVar = *m_boundVar;
		m_isEditing = true;
	}

}

void MenuVar<class T>::endEdit()
{
	if (m_isEditing) {
		*m_boundVar = m_scratchVar;
		m_isEditing = false;
	}
}

void MenuVar<class T>::IncreaseValue(int incBy)
{
	if (isEditing) {
		if (m_constrainValue) {
			if (m_scratchVar < m_max) {
				m_scratchVar+= incBy;
			}
		}
		else{
			m_scratchVar+= incBy;
		}
	}
}

void MenuVar<class T>::DecreaseValue(int decBy)
{
	if (isEditing) {
		if (m_constrainValue) {
			if (m_scratchVar > m_min) {
				m_scratchVar-= decBy;
			}
		}
		else {
			m_scratchVar-= decBy;
		}
	}
}

void MenuVar<class T>::resync()
{
	m_scratchVar = *m_boundVar;
}

bool MenuVar<class T>::isEditing()
{
	return m_isEditing;
}

void MenuVar<class T>::displaySelf(LiquidCrystal_I2C* display, int iIndex)
{
	display->print(m_displayname);
	display->print(":");
	display->print(m_scratchVar);
	if (iIndex == m_itemIndex) {
		display->print("#");
	}
	else {
		display->print(" ");
	}
}
*/