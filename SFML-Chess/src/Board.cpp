#include <Board.hpp>

Board::Board()
{
	std::string fileName = "chess-board.png";
	if (!mTexture.loadFromFile("assets/" + fileName)) std::cout << "Can't open " + fileName << std::endl;
	mSprite.setTexture(mTexture);
}

void Board::draw(sf::RenderWindow& window)
{
	window.draw(mSprite);
}

const sf::Uint16   Board::TILESIZE = 100;
const sf::Vector2i Board::TILECOUNT = { 8,8 };
const sf::Vector2i Board::DIM = { 800,800 };