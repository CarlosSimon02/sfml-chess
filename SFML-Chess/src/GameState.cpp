#include "GameState.hpp"

GameState::GameState()
{}

void GameState::display(sf::RenderWindow& window)
{
	for (auto& drawable : mDrawables) window.draw(*drawable);
}

void GameState::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	while (window.waitEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (mOldMousePos >= 0)
			{
				int newMousePos = Board::getBufferPosition({ sf::Mouse::getPosition(window).x / Board::TILESIZE, sf::Mouse::getPosition(window).y / Board::TILESIZE });
				if (mHighlights.isInPositionChoices(Board::getVectorPosition(newMousePos)))
				{
					mPiecesBuffer.movePiece(mOldMousePos, newMousePos);
					mPiecesBuffer.setTurnSide((mPiecesBuffer.getTurnSide() == Side::Black) ? Side::White : Side::Black);
				}
				mHighlights.clear();
				mOldMousePos = -1;
				return;
			}
			else if (mPiecesBuffer.hasPiece({ sf::Mouse::getPosition(window).x / Board::TILESIZE, sf::Mouse::getPosition(window).y / Board::TILESIZE }, mPiecesBuffer.getTurnSide()))
			{
				mOldMousePos = Board::getBufferPosition({ sf::Mouse::getPosition(window).x / Board::TILESIZE, sf::Mouse::getPosition(window).y / Board::TILESIZE });
				mHighlights.setPositions(mPiecesBuffer[mOldMousePos]->createPositionChoices(mPiecesBuffer));
				return;
			}
		}
	}
}
