#include "c2dpch.h"
#include "Board.h"
#include "Pawn.h"

namespace C2DGame
{
	Board::Board()
		:Behaviour("Board")
	{
		int mod = 0;
		for (size_t y = 0; y < 8; ++y)
		{
			mod = y % 2;
			for (size_t x = 0; x < 8; x++)
			{
				std::string file = (bool)((x + mod) % 2) ? "assets/JohnPablok_ChessSet/square_brown_light.png" : "assets/JohnPablok_ChessSet/square_gray_light.png";
				m_Blocks.push_back(new Pawn(file, x % 2, glm::vec3(0.5f + x, -0.5f - (y), 0.0f), 0.05f / 8 * 10));
			}
		}
	}

	void Board::OnStart()
	{
		for (auto& b : m_Blocks)
			b->OnStart();
	}

	void Board::OnUpdate(float deltaTime)
	{
		for (auto& b : m_Blocks)
			b->OnUpdate(deltaTime);
	}

	void Board::OnDestroy()
	{
		for (auto& b : m_Blocks)
			b->OnDestroy();
	}
}