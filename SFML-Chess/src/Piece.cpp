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
	mSprite.setPosition({ (float)boardPos.x * Board::TILESIZE, (float)boardPos.y * Board::TILESIZE });
}

sf::Sprite Piece::getSprite() const
{
	return mSprite;
}

sf::Vector2i Piece::getPos() const
{
	return mPos;
}

std::vector<sf::Vector2i> Piece::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	return std::vector<sf::Vector2i>();
}

std::vector<sf::Vector2i> Piece::getMoveDirections() const
{
	return mMoveDirections;
}

Piece::Side Piece::getSide() const
{
	return mSide;
}
