#pragma once
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "key.h"
#include "core/glm_math.h"
#include <vector>

namespace Nata
{
#define MAX_MOUSE_BUTTONS 32

	enum KeyState
	{
		None, Down, Hold, Up
	};

	struct KeyAction
	{
		bool Current;
		bool Previous;
		KeyState State;
	};

	class NInput
	{
	protected:
		KeyAction m_Keys[GLFW_KEY_LAST];
		KeyAction m_MouseBtns[MAX_MOUSE_BUTTONS];
		double m_Mx;
		double m_My;

	public:
		NInput();
		~NInput();
		void Init();
		void Clear();
		void Tick();

		bool GetKeyHold(int key) const;
		bool GetKeyDown(int key) const;
		bool GetKeyUp(int key) const;

		bool GetMouseDown(int button) const;

		void SetKeyState(int key, bool state);
		void SetMouseState(int mouseBtn, bool state);
		void SetCursorPos(double x, double y);

		vec2 GetMousePos();

	protected:
		void EvaluateKeyActions(KeyAction data[], int size);
	};

	extern NInput* input;
}