#pragma once
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "key.h"
#include "core/glm_math.h"

namespace Nata
{
#define MAX_MOUSE_BUTTONS 32

	struct ActionState
	{
		bool Current;
		bool Previous;
	};

	class NInput
	{
	public:
		ActionState m_Keys[GLFW_KEY_LAST];
		ActionState m_MouseBtns[MAX_MOUSE_BUTTONS];
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

	};

	extern NInput* input;
}