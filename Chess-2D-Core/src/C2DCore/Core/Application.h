#pragma once
#include "C2DCore.h"
#include "Window.h"
#include "Behaviour.h"
#include "../Events/EventManager.h"
#include <GLFW/glfw3.h>

namespace C2DCore
{
	class Application
	{
	public:
		Application(const std::string& name = "New Application", uint32_t width = 720, uint32_t height = 360);
		virtual ~Application();
		
		virtual void Run();
		virtual void OnEvent(Event& event);

		virtual void OnWindowCloseEvent(Event& event);

		void AddBehaviour(Behaviour* behaviour);
		void RemoveBehaviour(Behaviour* behaviour);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		std::unique_ptr<Window> m_Window;
		std::vector<Behaviour*> m_Behaviours;
		bool m_Running = true;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};
}
