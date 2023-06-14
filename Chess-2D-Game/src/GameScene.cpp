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
		for (size_t y = 0; y < 2; y++)
		{
			for (size_t x = 0; x < 8; x++)
			{
				m_GameObjects.push_back(new Pawn("assets/JohnPablok_ChessSet/b" + files[x + (y * 8)] + ".png", 0, glm::vec3(0.5f + x, -0.5f - (y), 0.0f), 0.05f / 8 * 10));
			}
		}

		for (size_t y = 0; y < 2; y++)
		{
			for (size_t x = 0; x < 8; x++)
			{
				m_GameObjects.push_back(new Pawn("assets/JohnPablok_ChessSet/w" + files[x + (y * 8)] + ".png", 0, glm::vec3(0.5f + x, -7.5f + (y), 0.0f), 0.05f / 8 * 10));
			}
		}
		m_GameObjects.push_back(new Board());

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
		if (e.GetEventType() == WindowResizeEvent::GetStaticEventType())
		{
			auto& sizeEvent = (WindowResizeEvent&)(e);
			glViewport(0, 0, sizeEvent.Width, sizeEvent.Height);
		}

		for (auto& p : m_GameObjects)
			p->OnEvent(e);
	}

	void GameScene::OnImGuiRender()
	{
		for (auto& p : m_GameObjects)
			p->OnImGuiRender();
	}
}
