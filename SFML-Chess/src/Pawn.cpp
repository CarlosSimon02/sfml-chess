#include "Pawn.hpp"

Pawn::Pawn(Side side, const sf::Vector2i& position)
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

std::vector<sf::Vector2i> Pawn::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	std::vector<sf::Vector2i> positionChoicesList;
	if (getSide() != piecesBuffer.getTurnSide())
		return std::vector<sf::Vector2i>{ getPos(),{getPos().x + getMoveDirs()[1].dir.x, getPos().y + getMoveDirs()[1].dir.y}, { getPos().x + getMoveDirs()[2].dir.x, getPos().y + getMoveDirs()[2].dir.y }};

	positionChoicesList.push_back(getPos());

	if (getState() == State::Moved) getMoveDirs()[0].range = 1;

	for (size_t i = 0; i < getMoveDirs().size(); i++)
	{
		for (size_t j = 1;
			(j <= getMoveDirs()[i].range) &&
			!Board::posIsOutOfBounds({ getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }) &&
			(i == 0 && !piecesBuffer.hasPiece({ getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }) ||
			((i == 1 || i == 2) && piecesBuffer.hasPiece({ getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }, (getSide() == Side::Black) ? Side::White : Side::Black)) ||
			i == 2 && getPos() == piecesBuffer.getEnpassantPos().first || 
			i == 1 && getPos() == piecesBuffer.getEnpassantPos().second);
			j++)
		{
			sf::Vector2i currentPos = { getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j };
			sf::Vector2i kingPos = piecesBuffer.getPiecesPosByType(Type::King, getSide())[0];

			if (!piecesBuffer.kingIsInCheck(getPos(), currentPos, getSide())) positionChoicesList.push_back(currentPos);
			if (piecesBuffer.hasPiece(currentPos, (getSide() == Side::Black) ? Side::White : Side::Black)) break;
		}
	}
	return positionChoicesList;
}