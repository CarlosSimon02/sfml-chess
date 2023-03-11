#include "Game.hpp"

Game::Game()
	: mWindow(sf::VideoMode(800, 800), "SFML-Chess")
{}

void Game::run()
{
	sf::Event e;
	std::vector<sf::Drawable*> drawables = { 
		&mBoard, 
		&mHighlights, 
		&mPiecesBuffer };

	int clickedMousePos = -1;

	while (mWindow.isOpen())
	{
		mWindow.clear();
		for (auto& drawable : drawables) mWindow.draw(*drawable);
		mWindow.display();

		while (mWindow.waitEvent(e))
		{
			if (e.type == sf::Event::Closed) mWindow.close();

			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (clickedMousePos >= 0) 
				{
					mPiecesBuffer.movePiece(clickedMousePos, Board::getBufferPosition(sf::Mouse::getPosition(mWindow)));
					clickedMousePos = -1;
					break;
				}
				clickedMousePos = Board::getBufferPosition(sf::Mouse::getPosition(mWindow));
				mHighlights.setSquares(mPiecesBuffer[clickedMousePos]->createPositionChoices(mPiecesBuffer));
				break;
			}
		}
	}
}