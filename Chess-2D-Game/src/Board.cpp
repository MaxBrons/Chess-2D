#include "c2dpch.h"
#include "Board.h"
#include "Pawn.h"

namespace C2DGame
{
	Board::Board(bool even, const std::string& texturePath)
		:Behaviour("Board"), m_Even(even), m_TexturePath(texturePath)
	{
	}

	void Board::OnStart()
	{
		auto& app = Application::Get();
		glm::vec2 windowSize = glm::vec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		m_BlockSize = glm::vec2(windowSize.x / 8, windowSize.y / 8);

		float vertexArray[(4 * 4) * (8 * 8)] = {};
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				vertexArray[0 + (16 * x) + (128 * y)] = x;
				vertexArray[1 + (16 * x) + (128 * y)] = -y;
				vertexArray[2 + (16 * x) + (128 * y)] = 0.0f;
				vertexArray[3 + (16 * x) + (128 * y)] = 0.0f;
				vertexArray[4 + (16 * x) + (128 * y)] = x;
				vertexArray[5 + (16 * x) + (128 * y)] = -(y + 1);
				vertexArray[6 + (16 * x) + (128 * y)] = 0.0f;
				vertexArray[7 + (16 * x) + (128 * y)] = 1.0f;
				vertexArray[8 + (16 * x) + (128 * y)] = x + 1;
				vertexArray[9 + (16 * x) + (128 * y)] = -y;
				vertexArray[10 + (16 * x) + (128 * y)] = 1.0f;
				vertexArray[11 + (16 * x) + (128 * y)] = 0.0f;
				vertexArray[12 + (16 * x) + (128 * y)] = x + 1;
				vertexArray[13 + (16 * x) + (128 * y)] = -(y + 1);
				vertexArray[14 + (16 * x) + (128 * y)] = 1.0f;
				vertexArray[15 + (16 * x) + (128 * y)] = 1.0f;
			}
		}

		m_VA = new VertexArray();
		m_VA->Bind();

		m_VB = new VertexBuffer(vertexArray, sizeof(vertexArray));
		M_VBL = new VertexBufferLayout();

		M_VBL->Push<float>(2);
		M_VBL->Push<float>(2);

		m_VA->AddBuffer(*M_VBL);

		unsigned int indexArray[6 * 4 * 8] = {};

		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				if (((x + (m_Even ? 0 : 1)) % 2))
				{
					indexArray[0 + (6 * (x / 2)) + (24 * y)] = x + 0 + (3 * x) + (32 * y);
					indexArray[1 + (6 * (x / 2)) + (24 * y)] = x + 1 + (3 * x) + (32 * y);
					indexArray[2 + (6 * (x / 2)) + (24 * y)] = x + 2 + (3 * x) + (32 * y);
					indexArray[3 + (6 * (x / 2)) + (24 * y)] = x + 2 + (3 * x) + (32 * y);
					indexArray[4 + (6 * (x / 2)) + (24 * y)] = x + 3 + (3 * x) + (32 * y);
					indexArray[5 + (6 * (x / 2)) + (24 * y)] = x + 1 + (3 * x) + (32 * y);
					m_BlockPositions.push_back(glm::vec2(windowSize.x / 8 * x, windowSize.y / 8 * y));
					continue;
				}
			}
			m_Even = !m_Even;
		}

		m_IB = new IndexBuffer(indexArray, sizeof(indexArray) / sizeof(unsigned int));

		m_Shader = Shader::FromGLSLTextFiles("assets/test.vert.glsl", "assets/test.frag.glsl");

		m_Texture = new Texture(m_TexturePath);

		m_VA->Unbind();
		m_VB->Unbind();
		m_IB->Unbind();
		m_Shader->Unbind();
	}

	void Board::OnUpdate(float deltaTime)
	{
		m_Shader->Bind();

		glm::mat4 proj = glm::ortho(-m_OrthoSize, m_OrthoSize, -m_OrthoSize, m_OrthoSize, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-m_ModelPosition.x, m_ModelPosition.y, 0.0f));
		m_VPM = proj * view * model;

		m_Shader->SetUniform4f("u_MVP", m_VPM);

		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		m_Renderer.Draw(*m_VA, *m_IB, *m_Shader);
	}

	void Board::OnImGuiRender()
	{
		ImGui::Text(GetName().c_str());
		ImGui::DragFloat("x", &m_ModelPosition.x, 0.05f);
		ImGui::DragFloat("y", &m_ModelPosition.y, 0.05f);
		ImGui::DragFloat("ortho", &m_OrthoSize, 0.05f);
		ImGui::Spacing();
	}

	void Board::OnDestroy()
	{
		m_VA->OnDestroy();
		m_VB->OnDestroy();
		m_IB->OnDestroy();
	}

	void Board::OnEvent(Event& e)
	{
		if (e.GetEventType() == MouseMovedEvent::GetStaticEventType())
		{
			auto& ev = (MouseMovedEvent&)e;
			m_MousePos = glm::vec2(ev.MouseX, ev.MouseY);
		}

		if (e.GetEventType() == MouseButtonPressedEvent::GetStaticEventType())
		{
			auto& it = std::find_if(m_BlockPositions.begin(), m_BlockPositions.end(), [&](glm::vec2& b)
				{
					return (m_MousePos.x >= b.x) && (m_MousePos.x < b.x + m_BlockSize.x) && (m_MousePos.y >= b.y) && (m_MousePos.y < b.y + m_BlockSize.y);
				});
			m_SelectedTile = (it != m_BlockPositions.end()) ? *it : glm::vec2(-1);
		}
	}
}