#include "c2dpch.h"
#include "Application.h"

namespace C2DCore
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, unsigned int width, unsigned int height)
	{
		if (s_Instance != nullptr)
			return;
		s_Instance = this;

		EventSystem::EventManager::Get().OnEvent += BIND_ACTION_FN_PM(Application::OnEvent, 1);

		m_Window = std::make_unique<Window>(WindowSettings(name, width, height, true));

		m_ImGuiBehaviour = new ImGuiBehaviour();
		AddBehaviour(m_ImGuiBehaviour);
	}

	Application::~Application()
	{
		EventSystem::EventManager::Get().OnEvent -= BIND_ACTION_FN_PM(Application::OnEvent, 1);

		for (auto behaviour : m_Behaviours)
		{
			behaviour->OnDestroy();
			delete behaviour;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			float deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (auto behaviour : m_Behaviours)
				behaviour->OnUpdate(m_LastFrameTime);

			m_ImGuiBehaviour->Begin();
			for (auto behaviour : m_Behaviours)
				behaviour->OnImGuiRender();
			m_ImGuiBehaviour->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		for (auto behaviour : m_Behaviours)
			behaviour->OnEvent(event);

		if (event.GetEventType() == WindowCloseEvent::GetStaticEventType())
			m_Running = false;
	}

	void Application::AddBehaviour(Behaviour* behaviour)
	{
		m_Behaviours.emplace(m_Behaviours.begin(), behaviour);
		behaviour->OnStart();
	}

	void Application::RemoveBehaviour(Behaviour* behaviour)
	{
		auto it = std::find(m_Behaviours.begin(), m_Behaviours.end(), behaviour);
		if (it != m_Behaviours.end())
		{
			(*it)->OnDestroy();
			m_Behaviours.erase(it);
			delete* it;
		}
	}
}

