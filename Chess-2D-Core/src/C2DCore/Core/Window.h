#pragma once
#include "../Events/EventManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace C2DCore
{
	using namespace EventSystem;

	struct WindowSettings
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		float Ratio;

		bool VSync;

		WindowSettings() = default;
		WindowSettings(const std::string& Title, const unsigned int& Width, const unsigned int& Height, bool VSync)
			: Title(Title), Width(Width), Height(Height), Ratio(Width/Height), VSync(VSync)
		{
		}
	};

	class Window
	{
	public:
		Window(const WindowSettings& settings);
		virtual ~Window() = default;

		void OnUpdate();

		inline const std::string& GetTitle() const { return m_Settings.Title; }
		inline unsigned int GetWidth() const { return m_Settings.Width; }
		inline unsigned int GetHeight() const { return m_Settings.Height; }
		inline WindowSettings& GetSettings() { return m_Settings; }

		inline void SetVSync(bool enabled);
		inline bool IsVSync() const;

		inline GLFWwindow* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowSettings& settings);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		WindowSettings m_Settings;
	};
}
