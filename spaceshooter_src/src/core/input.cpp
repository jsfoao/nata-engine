#include "input.h"

namespace Nata
{
	NInput::NInput()
	{
		m_Mx = 0;
		m_My = 0;

		for (size_t i = 0; i < GLFW_KEY_LAST; i++)
		{
			m_Keys[i].Current = 0;
			m_Keys[i].Previous = 0;
			m_Keys[i].State = None;
		}

		for (size_t i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			m_MouseBtns[i].Current = 0;
			m_MouseBtns[i].Previous = 0;
			m_MouseBtns[i].State = None;
		}
	}

	NInput::~NInput()
	{
	}

	void NInput::Init()
	{
	}

	void NInput::Tick()
	{
		EvaluateKeyActions(m_Keys, GLFW_KEY_LAST);
		EvaluateKeyActions(m_MouseBtns, MAX_MOUSE_BUTTONS);
	}

	bool NInput::GetKeyHold(int key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;

		return m_Keys[key].State == KeyState::Hold || m_Keys[key].State == KeyState::Down;
	}

	bool NInput::GetKeyDown(int key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;

		return m_Keys[key].State == KeyState::Down;
	}

	bool NInput::GetKeyUp(int key) const
	{
		if (key >= GLFW_KEY_LAST)
			return false;

		return m_Keys[key].State == KeyState::Up;
	}


	bool NInput::GetMouseDown(int code) const
	{
		if (code >= MAX_MOUSE_BUTTONS)
			return false;

		return m_MouseBtns[code].Current;
	}

	void NInput::EvaluateKeyActions(KeyAction data[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i].Current == true && data[i].Previous == false)
			{
				data[i].State = KeyState::Down;
				data[i].Previous = true;
			}
			else if (data[i].Current == false && data[i].Previous == true)
			{
				data[i].State = KeyState::Up;
				data[i].Previous = false;
			}
			else if (data[i].Current == true && data[i].Previous == true)
			{
				data[i].State = KeyState::Hold;
			}
			else if (data[i].Current == false && data[i].Previous == false)
			{
				data[i].State = KeyState::None;
			}
		}
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