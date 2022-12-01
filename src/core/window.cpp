#include "window.h"

namespace Nata
{
	NWindow::NWindow(const char* title, int width, int height)
	{
		m_Renderer = new NRenderer();
		m_Title = title;
		m_Width = width;
		m_Height = height;

		//if (!Init())
		//{
		//	glfwTerminate();
		//}
	}

	NWindow::~NWindow()
	{
		glfwTerminate();
	}

	bool NWindow::Init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		std::cout << glfwGetVersionString() << std::endl;

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to created window!" << std::endl;
			return false;
		}

		glfwSetWindowUserPointer(m_Window, this);
		Bind();
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW!" << std::endl;
			return false;
		}

		glViewport(0, 0, m_Width, m_Height);


		m_Input = new NInput();

		if (!m_Input)
		{
			std::cout << "Failed to create input!" << std::endl;
		}

		//// Callbacks
		//glfwSetKeyCallback(m_Window, key_callback); 
		//glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		//glfwSetCursorPosCallback(m_Window, cursor_pos_callback);
		return true;
	}

	void NWindow::Clear()
	{
		Bind();
		glClearColor(.15f, .15f, .15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void NWindow::Bind()
	{
		glfwMakeContextCurrent(m_Window);
	}

	bool NWindow::Closed()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void NWindow::Update()
	{
		m_Renderer->Flush();
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL error: " << error << std::endl;
		}

		// Checks if any events are triggered (keyboard input or mouse input)
		glfwPollEvents();
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);
	}

	//
	// CALLBACKS
	//
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		NWindow* win = (NWindow*)glfwGetWindowUserPointer(window);
		win->GetInput()->SetKeyState(key, action != GLFW_RELEASE);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		NWindow* win = (NWindow*)glfwGetWindowUserPointer(window);
		win->GetInput()->SetMouseState(button, action != GLFW_RELEASE);
	}

	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
	{
		NWindow* win = (NWindow*)glfwGetWindowUserPointer(window);
		win->GetInput()->SetCursorPos(xpos, ypos);
	}
}