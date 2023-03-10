#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include "Pawn.hpp"

class Game
{
public:
	Game();
	void run();

private:
	sf::RenderWindow mWindow;

	std::array<std::unique_ptr<Piece>, 64> mPiecesBuffer;
	Board mBoard;
};