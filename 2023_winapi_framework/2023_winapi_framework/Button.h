#pragma once
#include "Object.h" 

class Button :
	public Object
{
public:
	Button(void(*_action)());
	~Button();

private:
	void(*m_pAction)();
};

