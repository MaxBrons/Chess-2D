#include "c2dpch.h"
#include "GameScene.h"

namespace C2DGame
{
	void GameScene::OnStart()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_VA = new VertexArray();
		m_VA->Bind();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		m_VB = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
		M_VBL = new VertexBufferLayout();

		M_VBL->Push<float>(2);
		M_VBL->Push<float>(2);
		m_VA->AddBuffer(*M_VBL);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_IB = new IndexBuffer(indices, 6);

		m_Shader = Shader::FromGLSLTextFiles("assets/test.vert.glsl", "assets/test.frag.glsl");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_MVP", m_VPM);

		m_Texture = new Texture("");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		glm::mat4 proj = glm::ortho(-0.5f * m_Ratio, 0.5f * m_Ratio, -0.5f * m_Ratio, 0.5f * m_Ratio, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
		m_VPM = proj * view * model;

		m_VA->Unbind();
		m_VB->Unbind();
		m_IB->Unbind();
		m_Shader->Unbind();
	}

	void GameScene::OnUpdate(float deltaTime)
	{
		m_Renderer.Clear();

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_MVP", m_VPM);
		m_Shader->SetUniform1i("u_Texture", 0);

		m_Renderer.Draw(*m_VA, *m_IB, *m_Shader);
	}

	void GameScene::OnDestroy()
	{
		m_VA->OnDestroy();
		m_VB->OnDestroy();
		m_IB->OnDestroy();
	}

	void GameScene::OnEvent(Event& e)
	{
		if (e.GetEventType() == WindowResizeEvent::GetStaticEventType())
		{
			auto& sizeEvent = (WindowResizeEvent&)(e);
			m_Ratio = sizeEvent.Width / sizeEvent.Height;
			glViewport(0, 0, sizeEvent.Width, sizeEvent.Height);
		}
	}

	void GameScene::OnImGuiRender()
	{
	}
}
