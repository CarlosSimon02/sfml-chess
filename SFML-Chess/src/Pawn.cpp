#include "Pawn.hpp"

#include <numeric>

Pawn::Pawn(Side side, sf::Vector2i position)
	: Piece(Type::Pawn, side, position, (Side::Black == side) ?
		std::vector<MoveDir>{
			{ { 0, 1}, 2 },
			{ {-1, 1}, 1 }, //for capturing
			{ { 1, 1}, 1 },
} :
	std::vector<MoveDir>{
		{ { 0,-1}, 2 },
		{ {-1,-1}, 1 }, //for capturing
		{ { 1,-1}, 1 },
			})
{
	if (getSide() == Side::White && getPos().y != 6 &&
		getSide() == Side::White && getPos().y != 1) setState(State::Moved);
}

std::vector<sf::Vector2i> Pawn::validPosList(PiecesBuffer& piecesBuffer)
{
	std::vector<sf::Vector2i> positionChoicesList;

	if (getSide() != piecesBuffer.getPlygSide())
		return std::vector<sf::Vector2i>{ getPos(),
			{ getPos() + getMoveDirs()[1].dir }, 
			{ getPos() + getMoveDirs()[2].dir }};

	positionChoicesList.push_back(getPos());

	if (getState() == State::Moved) getMoveDirs()[0].range = 1;

	for (const MoveDir& movedir : getMoveDirs())
		for (size_t j = 1; j <= movedir.range; j++)
			if (isValidPos({ getPos() + (movedir.dir * (int)j) }, piecesBuffer))
				positionChoicesList.push_back({ getPos() + (movedir.dir * (int)j) });
	return positionChoicesList;
}

bool Pawn::isValidPos(sf::Vector2i pos, PiecesBuffer& buff)
{
	sf::Vector2i dir = ((pos - getPos()) / std::gcd(pos.x - getPos().x, pos.y - getPos().y));

	bool canBeCaptured = ((dir == getMoveDirs()[0].dir && !buff.hasPiece(pos)) ||
		((dir == getMoveDirs()[1].dir || dir == getMoveDirs()[2].dir) && buff.hasPiece(pos, (getSide() == Side::Black) ? Side::White : Side::Black)) ||
		(dir == getMoveDirs()[2].dir && 
			getPos() + sf::Vector2i{ 1,0 } == buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getPos() &&
			buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getLastMoveDirUsed().range == 2) ||
		(dir == getMoveDirs()[1].dir && 
			getPos() + sf::Vector2i{-1,0 } == buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getPos() &&
			buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getLastMoveDirUsed().range == 2));

	if (!Board::posIsOOB(pos) &&
		canBeReach(pos, buff) &&
		canBeCaptured &&
		!buff.testCheck(getPos(), pos, getSide()))
		return true;

	return false;
}

void Pawn::setPos(const sf::Vector2i& pos, PiecesBuffer& buff)
{
	//for enpassant
	if (buff.hasPiece(buff.getLastMovedPiecePos(), (getSide() == Side::Black) ? Side::White : Side::Black, Type::Pawn) &&
		buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getLastMoveDirUsed().range == 2 &&
		(pos == sf::Vector2i{ getPos() + getMoveDirs()[2].dir } && getPos() + sf::Vector2i{ 1,0 } == buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getPos()) ||
		(pos == sf::Vector2i{ getPos() + getMoveDirs()[1].dir } && getPos() + sf::Vector2i{-1,0 } == buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getPos()))
	{
		buff[Board::getBufPos(buff[Board::getBufPos(buff.getLastMovedPiecePos())]->getPos())].reset();
	}

	//for promoting
	if (pos.y == ((getSide() == Side::White) ? 0 : 7))
		buff.setPromotingStat(true);

	setLastMoveDirUsed(pos);
	setSpritePos(pos);
}
