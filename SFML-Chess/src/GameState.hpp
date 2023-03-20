#pragma once

#include <SFML/Graphics.hpp>

#include "Highlights.hpp"
#include "PiecesBuffer.hpp"
#include "PromoteOption.hpp"

class GameState
{
public:
	GameState();
	void display(sf::RenderWindow& window);
	void handleEvents(sf::RenderWindow& window, sf::Event & event);
	void setGameOverStat();
	bool getGameOverStat();

private:
	Board mBoard;
	Highlights mHighlights;
	PiecesBuffer mPiecesBuffer;
	PromoteOption mPromoteOp;
	std::vector<sf::Drawable*> mDrawables = { &mBoard,&mHighlights,&mPiecesBuffer };

	int mOldMousePos = -1;
	bool mIsGameOver = false;
};