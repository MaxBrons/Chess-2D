#pragma once
#include "C2DCore.h"
#include "C2DCore/Core/Behaviour.h"
#include "C2DCore/Events/Event.h"
#include "C2DCore/Rendering/Rendering.h"

using namespace C2DCore;
using namespace C2DCore::EventSystem;

namespace C2DGame
{
	class Board : public Behaviour
	{
	public:
		Board();
		~Board() = default;

		void OnStart() override;
		void OnUpdate(float deltaTime) override;
		void OnDestroy() override;

	private:
		std::vector<Behaviour*> m_Blocks;
	};
}
