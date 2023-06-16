#pragma once
#include "C2DCore.h"
#include "C2DCore/Core/Behaviour.h"
#include "C2DCore/Events/Event.h"
#include "C2DCore/Rendering/Rendering.h"

using namespace C2DCore;
using namespace C2DCore::EventSystem;

namespace C2DGame
{
	class Pawn : public Behaviour
	{
	public:
		Pawn(const std::string& texture, unsigned int textureSlot, glm::vec3 position, glm::vec2 pixelPosition, float scale = 1.0f, unsigned int layer = 0);
		~Pawn() = default;


		void OnStart() override;
		void OnUpdate(float deltaTime) override;
		void OnDestroy() override;
		void OnEvent(Event& e) override;
		void OnImGuiRender() override;
		bool Move(glm::vec2 destination);

		inline glm::vec2 GetPixelPosition() const { return m_PixelPosition; }

	private:
		Renderer m_Renderer;
		Texture* m_Texture = nullptr;
		Shader* m_Shader = nullptr;

		VertexArray* m_VA = nullptr;
		VertexBuffer* m_VB = nullptr;
		VertexBufferLayout* M_VBL = nullptr;
		IndexBuffer* m_IB = nullptr;

		float m_Ratio = 16.0f / 9.0f;
		glm::mat4 m_VPM;

		glm::vec3 m_Position;
		glm::vec2 m_PixelPosition = glm::vec2();
		std::string m_TexturePath;
		float m_Scale = 1.0f;
		unsigned int m_Layer = 0;
		unsigned int m_TextureSlot = 0;
	};
}
