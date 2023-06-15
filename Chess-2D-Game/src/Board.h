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
		void OnImGuiRender() override;
		void OnDestroy() override;

	private:
		std::vector<Behaviour*> m_Blocks;

		Renderer m_Renderer;
		Texture* m_Texture = nullptr;
		Texture* m_Texture2 = nullptr;
		Shader* m_Shader = nullptr;

		VertexArray* m_VA = nullptr;
		VertexBuffer* m_VB = nullptr;
		VertexBufferLayout* M_VBL = nullptr;
		IndexBuffer* m_IB = nullptr;

		glm::mat4 m_VPM;
	};
}
