#include "pch.h"
#include "Button.h"

Button::Button(void(*_action)())
{
	m_pAction = _action;
}

Button::~Button()
{
}
