#pragma once
#include "C2DCore.h"
#include "C2DCore/Core/Behaviour.h"
#include "C2DCore/Rendering/Rendering.h"
#include "Pawn.h"

using namespace C2DCore;
namespace C2DGame
{
	class GameScene : public Behaviour
	{
	public:
		GameScene(const std::string& name)
			:Behaviour(name)
		{
		}
		virtual ~GameScene() = default;

		void OnStart() override;
		void OnUpdate(float deltaTime) override;
		void OnDestroy() override;
		void OnEvent(Event& e) override;
		void OnImGuiRender() override;

	private:
		std::vector<Behaviour*> m_GameObjects;
		Renderer m_Renderer;
		Pawn* m_CurrentSelectedPawn = nullptr;
		glm::vec2 m_MousePosition;
	};
}
