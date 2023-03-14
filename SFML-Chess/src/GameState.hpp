#pragma once

#include <SFML/Graphics.hpp>

#include "Highlights.hpp"
#include "PiecesBuffer.hpp"

class GameState
{
public:
	GameState();
	void display(sf::RenderWindow& window);
	void handleEvents(sf::RenderWindow& window, sf::Event & event);

private:
	Board mBoard;
	Highlights mHighlights;
	PiecesBuffer mPiecesBuffer;

	int mOldMousePos = -1;

	std::vector<sf::Drawable*> mDrawables = { &mBoard,&mHighlights,&mPiecesBuffer };
};