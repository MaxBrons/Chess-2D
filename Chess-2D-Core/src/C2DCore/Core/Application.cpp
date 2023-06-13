#include "c2dpch.h"
#include "Application.h"

namespace C2DCore
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, uint32_t width, uint32_t height)
	{
		if (s_Instance != nullptr)
			return;
		s_Instance = this;

		EventSystem::EventManager::Get().OnEvent += BIND_ACTION_FN_PM(Application::OnWindowCloseEvent, 1);
		EventSystem::EventManager::Get().OnEvent += BIND_ACTION_FN_PM(Application::OnEvent, 1);

		m_Window = std::make_unique<Window>(WindowSettings(name, width, height, true));
	}

	Application::~Application()
	{
		for (auto behaviour : m_Behaviours)
			delete behaviour;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			float deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (auto behaviour : m_Behaviours)
				behaviour->OnUpdate(deltaTime);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		for (auto behaviour : m_Behaviours)
			behaviour->OnEvent(event);
	}

	void Application::OnWindowCloseEvent(Event& event)
	{
		if (event.GetEventType() != WindowCloseEvent::GetStaticEventType())
			return;

		m_Running = false;
	}

	void Application::AddBehaviour(Behaviour* behaviour)
	{
		m_Behaviours.push_back(behaviour);
		behaviour->OnStart();
	}

	void Application::RemoveBehaviour(Behaviour* behaviour)
	{
		auto it = std::find(m_Behaviours.begin(), m_Behaviours.end(), behaviour);
		if (it != m_Behaviours.end())
		{
			(*it)->OnDestroy();
			m_Behaviours.erase(it);
			delete *it;
		}
	}
}
