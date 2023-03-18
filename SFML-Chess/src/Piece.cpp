#include "Piece.hpp"

#include <numeric>

Piece::Piece(const Type& type, const Side& side, sf::Vector2i pos, const std::vector<MoveDir>& moveDirs)
	: mType{ type }, mSide{ side }, mMoveDirs{ moveDirs }
{
	std::string fileName = "chess-pieces.png";
	if (!mTexture.loadFromFile("assets/chess-pieces.png")) std::cout << "Can't open " + fileName << std::endl;
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect({ (int)type * Board::TILESIZE, (int)side * Board::TILESIZE, Board::TILESIZE, Board::TILESIZE });
	mSprite.setPosition(static_cast<sf::Vector2f>(pos * (int)Board::TILESIZE));
}

void Piece::setPos(const sf::Vector2i& pos)
{
	mSprite.setPosition(static_cast<sf::Vector2f>(pos*(int)Board::TILESIZE));
}

sf::Sprite Piece::getSprite() const
{
	return mSprite;
}

sf::Vector2i Piece::getPos() const
{
	return static_cast<sf::Vector2i>(mSprite.getPosition()) / (int)Board::TILESIZE;
}

std::vector<sf::Vector2i> Piece::validPosList(PiecesBuffer& piecesBuffer)
{
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());

	for (const MoveDir& movedir : mMoveDirs)
		for (size_t j = 1; j <= movedir.range; j++)
			if (isValidPos({ getPos() + (movedir.dir * (int)j) }, piecesBuffer))
				positionChoicesList.push_back({ getPos() + (movedir.dir * (int)j) });
	return positionChoicesList;
}

std::vector<Piece::MoveDir>& Piece::getMoveDirs()
{
	return mMoveDirs;
}

Side Piece::getSide() const
{
	return mSide;
}

Type Piece::getType() const
{
	return mType;
}

void Piece::setState(State state)
{
	mState = state;
}

State Piece::getState() const
{
	return mState;
}

bool Piece::isValidPos(sf::Vector2i pos, PiecesBuffer& buff)
{
	if (!Board::posIsOOB(pos) && 
		canBeReach(pos, buff) &&
		!buff.hasPiece(pos,getSide()) &&
		!buff.testCheck(getPos(), pos, getSide()))
		return true;

	return false;
}

bool Piece::isInMoveDirs(sf::Vector2i dir)
{
	for (const MoveDir& movedir : mMoveDirs)
		if (dir == movedir.dir)
			return true;
	return false;
}

bool Piece::canBeReach(sf::Vector2i pos, PiecesBuffer& buff)
{	
	sf::Vector2i dir = ((pos - getPos()) / std::gcd(pos.x - getPos().x, pos.y - getPos().y));
	for (sf::Vector2i i{ getPos() + dir }; i != pos; i += dir)
		if (buff.hasPiece(i) && isInMoveDirs(dir))
			return false;
	return true;
}
