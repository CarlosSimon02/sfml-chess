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

	if (getSide() != piecesBuffer.getTurnSide())
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
		(dir == getMoveDirs()[2].dir && getPos() == buff.getEnpassantPos().first) ||
		(dir == getMoveDirs()[1].dir && getPos() == buff.getEnpassantPos().second));

	if (!Board::posIsOOB(pos) &&
		canBeReach(pos, buff) &&
		canBeCaptured &&
		!buff.testCheck(getPos(), pos, getSide()))
		return true;

	return false;
}
