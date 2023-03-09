#include "Game.hpp"

Game::Game()
	: mWindow(sf::VideoMode(800, 800), "SFML-Chess")
{
	std::array<int, 64> boardSetUp = 
	  { 41, 31, 21, 01, 11, 21, 31, 41,
		51, 51, 51, 51, 51, 51, 51, 51,
		-10, -10, -10, -10, -10, -10, -10, -10,
		-10, -10, -10, -10, -10, -10, -10, -10,
		-10, -10, -10, -10, -10, -10, -10, -10,
		-10, -10, -10, -10, -10, -10, -10, -10,
		50, 50, 50, 50, 50, 50, 50, 50,
		40, 30, 20, 00, 10, 20, 30, 40 };


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
			
		default:
			break;
		}
	}
}

void Game::run()
{
	sf::Event e;

	//load background
	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("assets/chess-board.png"))
		std::cout << "Can't load image" << std::endl;;
	sf::Sprite bgSprite(bgTexture);

	while (mWindow.isOpen())
	{
		mWindow.clear();
		mWindow.draw(bgSprite);

		for (size_t i = 0; i < mPiecesBuffer.size(); i++)
		{
			if (mPiecesBuffer[i] != NULL) {
				mPiecesBuffer[i]->setSpritePos({ int(i) % 8, int(i) / 8 });
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