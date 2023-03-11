#include "Pawn.hpp"

Pawn::Pawn(Side side)
	: Piece(Type::Pawn, side, (Side::Black == side) ?
	std::vector<sf::Vector2i>{ {0, 1}, { 0,2 }, { -1,1 }, { 1,1 } } :   
	std::vector<sf::Vector2i>{ {0, -1}, { 0,-2 }, { -1,-1 }, { 1,-1 } })
{}

std::vector<sf::Vector2i> Pawn::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());

	for (size_t i = 0; i < getMoveDirections().size(); i++)
	{
		sf::Vector2i currentPos = { getPos().x + getMoveDirections()[i].x, getPos().y + getMoveDirections()[i].y };

		if (Board::posIsOutOfBounds(currentPos)) continue;
		positionChoicesList.push_back(currentPos);
	}
	return positionChoicesList;
}