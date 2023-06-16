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
		Board(bool even, const std::string& texturePath);
		~Board() = default;

		void OnStart() override;
		void OnUpdate(float deltaTime) override;
		void OnImGuiRender() override;
		void OnDestroy() override;
		void OnEvent(Event& e) override;

		inline glm::vec2 GetSelectedTile() const { return m_SelectedTile; }

	private:
		Renderer m_Renderer;
		Texture* m_Texture = nullptr;
		Shader* m_Shader = nullptr;

		VertexArray* m_VA = nullptr;
		VertexBuffer* m_VB = nullptr;
		VertexBufferLayout* M_VBL = nullptr;
		IndexBuffer* m_IB = nullptr;

		glm::vec2 m_ModelPosition = { 4.0f, 4.0f };
		float m_OrthoSize = 4.0f;
		std::vector<glm::vec2> m_BlockPositions;

		bool m_Even = true;
		std::string m_TexturePath;
		glm::vec2 m_SelectedTile;
		glm::vec2 m_MousePos;
		glm::vec2 m_BlockSize;

		glm::mat4 m_VPM;
	};
}
