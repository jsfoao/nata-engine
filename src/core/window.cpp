#include "window.h"

namespace Nata
{
	Window::Window(const char* title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;

		if (!Init())
		{
			glfwTerminate();
		}
		LOG("Start Window");
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			LOG("Failed to initialize GLFW!");
			return false;
		}
		LOG(glfwGetVersionString());

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			LOG("Failed to created window!");
			return false;
		}
		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			LOG("Failed to initialize GLEW!");
			return false;
		}

		glViewport(0, 0, m_Width, m_Height);
		glfwSetWindowUserPointer(m_Window, this);

		// Callbacks
		glfwSetKeyCallback(m_Window, key_callback); 
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_pos_callback);

		m_Input = new Input();

		if (!m_Input)
		{
			LOG("Failed to create input!");
		}

		return true;
	}

	void Window::Clear() const
	{
		glClearColor(.15f, .15f, .15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::Closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::Update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL error: " << error << std::endl;
		}

		// Checks if any events are triggered (keyboard input or mouse inpit)
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
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->GetInput()->SetKeyState(key, action != GLFW_RELEASE);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->GetInput()->SetMouseState(button, action != GLFW_RELEASE);
	}

	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->GetInput()->SetCursorPos(xpos, ypos);
	}
}