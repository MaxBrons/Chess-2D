#include "c2dpch.h"
#include "GameScene.h"
#include "Pawn.h"
#include "Board.h"

namespace C2DGame
{
	void GameScene::OnStart()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::string files[] = {
			"_rook_png_1024px",
			"_knight_png_1024px",
			"_bishop_png_1024px",
			"_queen_png_1024px",
			"_king_png_1024px",
			"_bishop_png_1024px",
			"_knight_png_1024px",
			"_rook_png_1024px",
			"_pawn_png_1024px",
			"_pawn_png_1024px",
			"_pawn_png_1024px",
			"_pawn_png_1024px",
			"_pawn_png_1024px",
			"_pawn_png_1024px",
			"_pawn_png_1024px",
			"_pawn_png_1024px"
		};

		auto& app = Application::Get();
		float width = app.GetWindow().GetWidth();
		float height = app.GetWindow().GetHeight();

		for (size_t s_PosY = 0; s_PosY < 2; s_PosY++)
		{
			for (size_t s_PosX = 0; s_PosX < 8; s_PosX++)
			{
				m_GameObjects.push_back(new Pawn("assets/JohnPablok_ChessSet/b" + files[s_PosX + (s_PosY * 8)] + ".png", 0, glm::vec3(0.5f + s_PosX, -0.5f - (s_PosY), 0.0f), glm::vec2(width / 8 * s_PosX, height / 8 * s_PosY), 0.05f / 8 * 10));
			}
		}

		for (size_t s_PosY = 0; s_PosY < 2; s_PosY++)
		{
			for (size_t s_PosX = 0; s_PosX < 8; s_PosX++)
			{
				m_GameObjects.push_back(new Pawn("assets/JohnPablok_ChessSet/w" + files[s_PosX + (s_PosY * 8)] + ".png", 0, glm::vec3(0.5f + s_PosX, -7.5f + (s_PosY), 0.0f), glm::vec2(width / 8 * s_PosX, height - ((height / 8) * (s_PosY + 1))), 0.05f / 8 * 10));
			}
		}
		m_GameObjects.push_back(new Board(false, "assets/JohnPablok_ChessSet/square_brown_light.png"));
		m_GameObjects.push_back(new Board(true, "assets/JohnPablok_ChessSet/square_gray_light.png"));

		for (auto& p : m_GameObjects)
			p->OnStart();
	}

	void GameScene::OnUpdate(float deltaTime)
	{
		m_Renderer.Clear();
		for (auto& p : m_GameObjects)
			p->OnUpdate(deltaTime);
	}

	void GameScene::OnDestroy()
	{
		for (auto& p : m_GameObjects)
			p->OnDestroy();
	}

	void GameScene::OnEvent(Event& e)
	{
		for (auto& p : m_GameObjects)
			p->OnEvent(e);

		if (e.GetEventType() == WindowResizeEvent::GetStaticEventType())
		{
			auto& sizeEvent = (WindowResizeEvent&)(e);
			glViewport(0, 0, sizeEvent.Width, sizeEvent.Height);
		}

		if (e.GetEventType() == MouseMovedEvent::GetStaticEventType())
		{
			auto& mouseEvent = (MouseMovedEvent&)(e);
			m_MousePosition = glm::vec2(mouseEvent.MouseX, mouseEvent.MouseY);
		}

		if (e.GetEventType() == MouseButtonPressedEvent::GetStaticEventType())
		{
			for (auto& gameObject : m_GameObjects)
			{
				Pawn* pawn = dynamic_cast<Pawn*>(gameObject);
				if (pawn != nullptr)
				{
					auto& app = Application::Get();
					glm::vec2 windowSize = glm::vec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
					auto m_BlockSize = glm::vec2(windowSize.x / 8, windowSize.y / 8);
					auto pixelPos = pawn->GetPixelPosition();

					if ((m_MousePosition.x >= pixelPos.x) && (m_MousePosition.x < pixelPos.x + m_BlockSize.x) && (m_MousePosition.y >= pixelPos.y) && (m_MousePosition.y < pixelPos.y + m_BlockSize.y))
					{
						m_CurrentSelectedPawn = pawn;
						std::cout << "SELECTED A PAWN" << std::endl;
						break;
					}
				}
			}

			if (m_CurrentSelectedPawn != nullptr)
			{
				for (auto& gameObject : m_GameObjects)
				{
					Board* board = dynamic_cast<Board*>(gameObject);
					if (board != nullptr)
					{
						if (board->GetSelectedTile() != glm::vec2(-1))
						{
							if (m_CurrentSelectedPawn->Move(board->GetSelectedTile()))
								m_CurrentSelectedPawn = nullptr;
							break;
						}
					}
				}
			}
		}
	}

	void GameScene::OnImGuiRender()
	{
		for (auto& p : m_GameObjects)
			p->OnImGuiRender();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
