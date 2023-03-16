#include "Piece.hpp"

Piece::Piece(const Type& type, const Side& side, const sf::Vector2i& position, const std::vector<MoveDir>& moveDirs)
	: mType{ type }, mSide{ side }, mPos{ position }, mMoveDirs{ moveDirs }
{
	std::string fileName = "chess-pieces.png";
	if (!mTexture.loadFromFile("assets/chess-pieces.png")) std::cout << "Can't open " + fileName << std::endl;
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect({ (int)type * Board::TILESIZE, (int)side * Board::TILESIZE, Board::TILESIZE, Board::TILESIZE });
	mSprite.setPosition({ (float)position.x * Board::TILESIZE, (float)position.y * Board::TILESIZE });
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
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());

	for (size_t i = 0; i < getMoveDirs().size(); i++)
	{
		for (size_t j = 1;
			j <= getMoveDirs()[i].range &&
			!Board::posIsOutOfBounds({ getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }) &&
			((getSide() == piecesBuffer.getTurnSide()) ? !piecesBuffer.hasPiece({ getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }, getSide()) : true);
			j++)
		{
			sf::Vector2i currentPos = { getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j };
			sf::Vector2i kingPos = piecesBuffer.getPiecesPosByType(Type::King, getSide())[0];

			if(!piecesBuffer.kingIsInCheck(getPos(), currentPos, getSide())) positionChoicesList.push_back(currentPos);

			if (piecesBuffer.hasPiece(currentPos)) break;
		}
	}
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
