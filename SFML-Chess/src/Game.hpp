#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "Highlights.hpp"
#include "PiecesBuffer.hpp"

class Game
{
public:
	Game();
	void run();

private:
	sf::RenderWindow mWindow;

	Board mBoard;
	Highlights mHighlights;
	PiecesBuffer mPiecesBuffer;
};