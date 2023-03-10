#include "Piece.hpp"

Piece::Piece(const Type& type, const Side& side, const std::vector<sf::Vector2i>& moveDirections)
	: mType{ type }, mSide{ side }, mMoveDirections{ moveDirections }
{
	std::string fileName = "chess-pieces.png";
	if (!mTexture.loadFromFile("assets/chess-pieces.png")) std::cout << "Can't open " + fileName << std::endl;
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect({ (int)type * Board::TILESIZE, (int)side * Board::TILESIZE, Board::TILESIZE, Board::TILESIZE });
}

void Piece::setPos(const sf::Vector2i& boardPos)
{
	mPos = boardPos;
	mSprite.setPosition({ (float)boardPos.x * 100.f, (float)boardPos.y * 100.f });
}

void Piece::draw(sf::RenderWindow& window)
{
	window.draw(mSprite);
}
