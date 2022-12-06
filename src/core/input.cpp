#include "input.h"

namespace Nata
{
	NInput::NInput()
	{
		m_Mx = 0;
		m_My = 0;

		for (size_t i = 0; i < GLFW_KEY_LAST; i++)
		{
			m_Keys[i].Current = false;
			m_Keys[i].Previous = false;
		}

		for (size_t i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			m_MouseBtns[i].Current = false;
			m_MouseBtns[i].Previous = false;
		}
	}

	NInput::~NInput()
	{
	}

	void NInput::Init()
	{
	}

	void NInput::Clear()
	{
	}

	void NInput::Tick()
	{
		std::cout << "------" << std::endl;
		std::cout << "Previous: " << m_Keys[32].Previous << std::endl;
		std::cout << "Current: " << m_Keys[32].Current << std::endl;
		std::cout << "------" << std::endl;
	}

	bool NInput::GetKeyHold(int key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;

		return m_Keys[key].Current;
	}

	bool NInput::GetKeyDown(int key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;

		return m_Keys[key].Current == true && m_Keys[key].Previous == false;
	}

	bool NInput::GetKeyUp(int key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;

		return m_Keys[key].Current == false && m_Keys[key].Previous == true;
	}


	bool NInput::GetMouseDown(int code) const
	{
		if (code >= MAX_MOUSE_BUTTONS)
			return false;

		return m_MouseBtns[code].Current;
	}

	vec2 NInput::GetMousePos()
	{
		return vec2(m_Mx, m_My);
	}

	void NInput::SetKeyState(int code, bool state)
	{
		m_Keys[code].Previous = m_Keys[code].Current;
		m_Keys[code].Current = state;

	}

	void NInput::SetMouseState(int code, bool state)
	{
		m_Keys[code].Previous = m_Keys[code].Current;
		m_MouseBtns[code].Current = state;
	}
	void NInput::SetCursorPos(double x, double y)
	{
		m_Mx = x;
		m_My = y;
	}
}