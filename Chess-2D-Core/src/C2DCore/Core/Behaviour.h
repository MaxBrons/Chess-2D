#pragma once
#include "../Events/Event.h"

namespace C2DCore
{
	using namespace EventSystem;

	class Behaviour
	{
	public:
		Behaviour(const std::string& name = "")
			:m_Name(name)
		{
		}
		virtual ~Behaviour() = default;

		virtual void OnStart() {};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnDestroy() {};
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}

		std::string& GetName() { return m_Name; }

	private:
		std::string m_Name;
	};
}
