#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "core.h"
#include "core/input.h"
#include "renderer/renderer.hpp"

namespace Nata
{
	class NWindow
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;
		Input* m_Input;
		bool m_Closed;
		NRenderer* m_Renderer;

	public:
		NWindow(const char* name, int width, int height);
		~NWindow();
		void Update();
		bool Closed() const;
		void Clear() const;

		inline int GetWidth() const { return m_Width;  }
		inline int GetHeight() const { return m_Height;  }
		inline GLFWwindow* GetWindow() const { return m_Window; }
		inline Input* GetInput() const { return m_Input; }
		inline NRenderer* GetRenderer() const { return m_Renderer; }

	public:
		bool Init();
	};

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
}