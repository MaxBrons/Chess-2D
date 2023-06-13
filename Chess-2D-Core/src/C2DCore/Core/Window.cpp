#include "c2dpch.h"
#include "Window.h"

namespace C2DCore
{
	Window::Window(const WindowSettings& settings)
	{
		Init(settings);
	}

	void Window::Init(const WindowSettings& settings)
	{
		m_Settings = settings;
		glfwInit();
		glfwSetErrorCallback([](int error, const char* description)
			{
				std::cout << "ERROR " << error << ": " << description << std::endl;
			});

		m_Window = glfwCreateWindow((int)m_Settings.Width, (int)m_Settings.Height, m_Settings.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowUserPointer(m_Window, &m_Settings);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowSettings& data = *(WindowSettings*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				EventManager::Get().OnEvent(WindowResizeEvent(width, height));
			});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int posX, int posY)
			{
				EventManager::Get().OnEvent(WindowMovedEvent(posX, posY));
			});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focus)
			{
				if (focus == GLFW_TRUE)
					EventManager::Get().OnEvent(WindowFocusEvent());
				else
					EventManager::Get().OnEvent(WindowLostFocusEvent());
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				EventManager::Get().OnEvent(WindowCloseEvent());
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				if (action != GLFW_RELEASE)
					EventManager::Get().OnEvent(KeyPressedEvent(key, action - 1));
				else
					EventManager::Get().OnEvent(KeyReleasedEvent(key));
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t keycode)
			{
				EventManager::Get().OnEvent(KeyTypedEvent(keycode));
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				if (action == GLFW_PRESS)
					EventManager::Get().OnEvent(MouseButtonPressedEvent(button));
				else
					EventManager::Get().OnEvent(MouseButtonReleasedEvent(button));
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				EventManager::Get().OnEvent(MouseScrolledEvent(xOffset, yOffset));
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				EventManager::Get().OnEvent(MouseMovedEvent(xPos, yPos));
			});
	}

	void Window::OnUpdate()
	{
		if (m_Window == nullptr)
			return;
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	inline void Window::SetVSync(bool enabled)
	{
		m_Settings.VSync = enabled;
		glfwSwapInterval(enabled);
	}

	inline bool Window::IsVSync() const
	{
		return m_Settings.VSync;
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}
