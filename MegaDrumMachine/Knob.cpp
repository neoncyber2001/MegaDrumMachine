// 
// 
// 

#include "Knob.h"


void Knob::do_ints()
{
	attachInterrupt(digitalPinToInterrupt(m_pinA), Knob::getIsr(),HIGH);
}

void Knob::init()
{
	Knob::step = false;
	Knob::dir = false;
}

Knob::Knob(int pinA, int pinB, int init_value)
{
	m_pinA = pinA;
	m_pinB = pinB;
	m_value = init_value;
	m_cycle = false;
	m_min = -100;
	m_max = 100;
}




Knob::Knob(int pinA, int pinB, int init_value, int min, int max, bool cycle)
{
	m_pinA = pinA;
	m_pinB = pinB;
	m_value = init_value;
	m_cycle = cycle;
	m_min = min;
	m_max = max;
	
}

int Knob::getValue()
{
	return m_value;
}

void Knob::setRange(int min, int max, int val)
{
	m_min = min;
	m_max = max;
	m_value = val;
}

void Knob::setValue(int val)
{
	m_value = val;
}

void Knob::setCycle(bool cyc)
{
	m_cycle = cyc;
}

voidFuncPtr Knob::getIsr()
{
	return []()->void {
		digitalRead(this.m_pinA);
	};
}
