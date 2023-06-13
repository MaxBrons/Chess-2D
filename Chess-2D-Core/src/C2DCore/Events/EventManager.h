#pragma once
#include "Action.h"
#include "Event.h"

namespace C2DCore::EventSystem
{
	class EventManager
	{
	public:
		EventManager();
		virtual ~EventManager() = default;

		Action<Event&> OnEvent;

	public:
		inline static EventManager& Get() { return *s_Instance; }

	private:
		static EventManager* s_Instance;
	};
}
