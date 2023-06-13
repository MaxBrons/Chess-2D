#include "c2dpch.h"
#include "EventManager.h"

namespace C2DCore::EventSystem
{
	EventManager* EventManager::s_Instance = nullptr;

	EventManager::EventManager()
	{
		if (s_Instance != nullptr)
			return;
		s_Instance = this;
	}
}
