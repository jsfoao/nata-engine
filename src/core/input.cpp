#include "input.h"

namespace Nata
{
	Input::Input()
	{
		m_Mx = 0;
		m_My = 0;

		for (size_t i = 0; i < GLFW_KEY_LAST; i++)
		{
			m_Keys[i].current = false;
			m_Keys[i].previous = false;
		}

		for (size_t i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			m_MouseBtns[i].current = false;
			m_MouseBtns[i].previous = false;
		}
	}

	void Input::Init()
	{
	}

	bool Input::GetKeyDown(int code) const
	{
		if (code >= GLFW_KEY_LAST)
			return false;

		return m_Keys[code].current;
	}


	bool Input::GetMouseDown(int code) const
	{
		if (code >= MAX_MOUSE_BUTTONS)
			return false;
		
		return m_MouseBtns[code].current;
	}

	vec2 Input::GetMousePos()
	{
		return vec2(m_Mx, m_My);
	}

	void Input::SetKeyState(int code, bool state)
	{
		m_Keys[code].previous = m_Keys[code].current;
		m_Keys[code].current = state;
	}

	void Input::SetMouseState(int code, bool state)
	{
		m_Keys[code].previous = m_Keys[code].current;
		m_MouseBtns[code].current = state;
	}
	void Input::SetCursorPos(double x, double y)
	{
		m_Mx = x;
		m_My = y;
	}
}