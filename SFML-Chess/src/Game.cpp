#include "Game.hpp"

Game::Game()
	: mWindow(sf::VideoMode(800, 800), "SFML-Chess")
{
	std::array<int, 64> boardSetUp = 
	  { 41, 31, 21, 11, 01, 21, 31, 41,
		51, 51, 51, 51, 51, 51, 51, 51,
		-10, -10, -10, -10, -10, -10, -10, -10,
		-10, -10, -10, -10, -10, -10, -10, -10,
		-10, -10, -10, -10, -10, -10, -10, -10,
		-10, -10, -10, -10, -10, -10, -10, -10,
		50, 50, 50, 50, 50, 50, 50, 50,
		40, 30, 20, 10, 00, 20, 30, 40 };


	for (size_t i = 0; i < mPiecesBuffer.size(); i++)
	{
		switch (static_cast<Piece::Type>(boardSetUp[i] / 10))
		{
		case Piece::Type::Blank:
			mPiecesBuffer[i] = NULL;
			break;
		case Piece::Type::King:
			mPiecesBuffer[i].reset(new King(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Queen:
			mPiecesBuffer[i].reset(new Queen(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Bishop:
			mPiecesBuffer[i].reset(new Bishop(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Knight:
			mPiecesBuffer[i].reset(new Knight(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Rook:
			mPiecesBuffer[i].reset(new Rook(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Pawn:
			mPiecesBuffer[i].reset(new Pawn(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		}
	}
}

void Game::run()
{
	sf::Event e;

	while (mWindow.isOpen())
	{
		mWindow.clear();
		
		mBoard.draw(mWindow);
		for (size_t i = 0; i < mPiecesBuffer.size(); i++)
		{
			if (mPiecesBuffer[i] != NULL) 
			{
				mPiecesBuffer[i]->setPos({ (int)i % 8, (int)i / 8});
				mPiecesBuffer[i]->draw(mWindow);
			}
		}

		mWindow.display();

		while (mWindow.waitEvent(e))
		{
			if (e.type == sf::Event::Closed) mWindow.close();
		}
	}
}