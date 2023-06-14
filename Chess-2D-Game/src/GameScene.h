#pragma once
#include "C2DCore.h"
#include "C2DCore/Core/Behaviour.h"
#include "C2DCore/ImGui/ImGuiBehaviour.h"
#include "C2DCore/Rendering/Rendering.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "glad/glad.h"

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
		Renderer m_Renderer;
		Texture* m_Texture = nullptr;
		Shader* m_Shader = nullptr;

		VertexArray* m_VA = nullptr;
		VertexBuffer* m_VB = nullptr;
		VertexBufferLayout* M_VBL = nullptr;
		IndexBuffer* m_IB = nullptr;

		float m_Ratio = 16.0f/9.0f;
		glm::mat4 m_VPM;
	};
}
