#include "c2dpch.h"
#include "Board.h"
#include "Pawn.h"

namespace C2DGame
{
	Board::Board()
		:Behaviour("Board")
	{
	}

	void Board::OnStart()
	{
		m_VA = new VertexArray();
		m_VA->Bind();

		float vertexArray[(4 * 4) * (8 * 8)];

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

		m_VB = new VertexBuffer(vertexArray, sizeof(vertexArray));
		M_VBL = new VertexBufferLayout();

		M_VBL->Push<float>(2);
		M_VBL->Push<float>(2);
		m_VA->AddBuffer(*M_VBL);

		unsigned int indexArray[6 * 8 * 8];
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				indexArray[0 + (6 * x) + (48 * y)] = x +	 (3 * x) + (32 * y);
				indexArray[1 + (6 * x) + (48 * y)] = x + 1 + (3 * x) + (32 * y);
				indexArray[2 + (6 * x) + (48 * y)] = x + 2 + (3 * x) + (32 * y);
				indexArray[3 + (6 * x) + (48 * y)] = x + 2 + (3 * x) + (32 * y);
				indexArray[4 + (6 * x) + (48 * y)] = x + 3 + (3 * x) + (32 * y);
				indexArray[5 + (6 * x) + (48 * y)] = x + 1 + (3 * x) + (32 * y);
				for (int z = 0; z < 6; z++)
				{
					/*if ((z + 1) % 6 == 3 || (z + 1) % 6 == 0)
						continue;*/
					std::cout << vertexArray[z + (x * 6) + (y * 48)] << std::endl;
				}
			}
		}

		m_IB = new IndexBuffer(indexArray, sizeof(indexArray) / sizeof(unsigned int));

		m_Shader = Shader::FromGLSLTextFiles("assets/test.vert.glsl", "assets/test.frag.glsl");
		m_Shader->Bind();

		m_Texture = new Texture("assets/JohnPablok_ChessSet/square_brown_light.png");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		m_VA->Unbind();
		m_VB->Unbind();
		m_IB->Unbind();
		m_Shader->Unbind();
	}
	static float x = 2.5f, y = 2.5f;
	static float ortho = 5;
	void Board::OnUpdate(float deltaTime)
	{
		m_Shader->Bind();

		glm::mat4 proj = glm::ortho(-ortho, ortho, -ortho, ortho, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-x, -y, 0.0f));
		m_VPM = proj * view * model;

		m_Shader->SetUniform4f("u_MVP", m_VPM);

		m_VA->Bind();
		m_Renderer.Draw(*m_VA, *m_IB, *m_Shader);
	}

	void Board::OnImGuiRender()
	{
		ImGui::DragFloat("x", &x, 0.05f);
		ImGui::DragFloat("y", &y, 0.05f);
		ImGui::DragFloat("ortho", &ortho, 0.05f);
	}

	void Board::OnDestroy()
	{
		m_VA->OnDestroy();
		m_VB->OnDestroy();
		m_IB->OnDestroy();
	}
}