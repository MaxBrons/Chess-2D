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
		uint32_t Width;
		uint32_t Height;

		bool VSync;

		WindowSettings() = default;
		WindowSettings(const std::string& Title, const uint32_t& Width, const uint32_t& Height, bool VSync)
			: Title(Title), Width(Width), Height(Height), VSync(VSync)
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
		inline uint32_t GetWidth() const { return m_Settings.Width; }
		inline uint32_t GetHeight() const { return m_Settings.Height; }
		inline WindowSettings& GetSettings() { return m_Settings; }

		inline void SetVSync(bool enabled);
		inline bool IsVSync() const;

	private:
		virtual void Init(const WindowSettings& settings);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		WindowSettings m_Settings;
	};
}
