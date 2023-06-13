#pragma once
#include <C2DCore.h>
#include "C2DCore/Core/Behaviour.h"

using namespace C2DCore;
namespace C2DGame
{
	class GameBehaviour : public Behaviour
	{
	public:
		GameBehaviour(const std::string& name)
			:Behaviour(name)
		{
		}
		virtual ~GameBehaviour() = default;

		void OnStart() override;
		void OnUpdate(float deltaTime) override;
		void OnDestroy() override;
		void OnEvent(Event& e) override;

		GLuint CompileShader(GLenum type, const std::string& source);
		GLuint LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	private:
		std::string m_Shader_Frag, m_Shader_Vert;
		GLuint m_QuadVA, m_QuadVB, m_QuadIB;

		glm::vec4 m_SquareBaseColor = { 0.1f, 0.5f, 0.3f, 1.0f };
		glm::vec4 m_SquareAlternateColor = { 0.6f, 0.2f, 0.1f, 1.0f };
		glm::vec4 m_SquareColor = m_SquareBaseColor;

		glm::mat4 m_VPM;
	};
}
