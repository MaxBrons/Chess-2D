#include "c2dpch.h"
#include "Pawn.h"

namespace C2DGame
{
	Pawn::Pawn(const std::string& texture, unsigned int textureSlot, glm::vec3 position, glm::vec2 pixelPosition, float scale, unsigned int layer)
		:Behaviour("Pawn"), m_TextureSlot(textureSlot), m_TexturePath(texture), m_Position(position), m_PixelPosition(pixelPosition), m_Scale(scale), m_Layer(layer)
	{
	}

	void Pawn::OnStart()
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		m_VA = new VertexArray();
		m_VA->Bind();

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

		m_Texture = new Texture(m_TexturePath);
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		m_VA->Unbind();
		m_VB->Unbind();
		m_IB->Unbind();
		m_Shader->Unbind();
	}

	void Pawn::OnUpdate(float deltaTime)
	{
		float orthoOffset = (m_Position.z + m_Layer + 0.5f) / m_Scale;

		glm::mat4 proj = glm::ortho(0.0f, -orthoOffset, -orthoOffset, 0.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position.x, m_Position.y, 0.0f));
		m_VPM = proj * view * model;

		m_VA->Bind();
		m_IB->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_MVP", m_VPM);
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
		m_Renderer.Draw(*m_VA, *m_IB, *m_Shader);
	}

	void Pawn::OnDestroy()
	{
		m_VA->OnDestroy();
		m_VB->OnDestroy();
		m_IB->OnDestroy();
	}

	void Pawn::OnEvent(Event& e)
	{
		if (e.GetEventType() == WindowResizeEvent::GetStaticEventType())
		{
			auto& sizeEvent = (WindowResizeEvent&)(e);
			m_Ratio = sizeEvent.Width;
		}
	}

	void Pawn::OnImGuiRender()
	{
		ImGui::DragFloat3("Position", (float*)&m_Position, 0.005f);
		ImGui::InputFloat("Scale", (float*)&m_Scale, 0.0f, 10.0f);
	}

	bool Pawn::Move(glm::vec2 destination)
	{
		auto& app = Application::Get();
		glm::vec2 windowSize = glm::vec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		auto blockSize = glm::vec2(windowSize.x / 8, windowSize.y / 8);

		glm::vec2 delta = m_PixelPosition - destination;
		int deltaX = delta.x / blockSize.x;
		int deltaY = delta.y / blockSize.y;
		m_Position.x -= deltaX;
		m_Position.y += deltaY;
		m_PixelPosition = destination;
		std::cout << (deltaX != 0 || deltaY != 0) << std::endl;
		return deltaX != 0 || deltaY != 0;
	}
}