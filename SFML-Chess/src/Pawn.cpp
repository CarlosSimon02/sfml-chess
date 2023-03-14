#include "Pawn.hpp"

Pawn::Pawn(Side side, const sf::Vector2i& position)
	: Piece(Type::Pawn, side, position, (Side::Black == side) ?
		std::vector<sf::Vector2i>{ {0, 1}, { 0,2 }, { -1,1 }, { 1,1 } } :
		std::vector<sf::Vector2i>{ {0, -1}, { 0,-2 }, { -1,-1 }, { 1,-1 } })
{
	if (getSide() == Side::White && getPos().y != 6 &&
		getSide() == Side::White && getPos().y != 1) setState(State::Moved);
}

std::vector<sf::Vector2i> Pawn::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	auto posAt = [&](int index) {return sf::Vector2i{ getPos().x + getMoveDirections()[index].x, getPos().y + getMoveDirections()[index].y }; };
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());

	for (size_t i = 0; i < getMoveDirections().size(); i++)
	{
		sf::Vector2i currentPos = { getPos().x + getMoveDirections()[i].x, getPos().y + getMoveDirections()[i].y };

		if (!Board::posIsOutOfBounds(posAt((int)i)) &&
			i == 0 && !piecesBuffer.hasPiece(posAt(0)) ||
			(i == 1 && getState() == State::Static && !piecesBuffer.hasPiece(posAt(1)) && !piecesBuffer.hasPiece(posAt(0))) ||
			((i == 2 || i == 3) && (piecesBuffer.hasPiece(posAt((int)i), (getSide() == Side::Black) ? Side::White : Side::Black))) ||
			(i == 2) && mCanEnpassant.first || (i==2) && mCanEnpassant.second)
		{
			positionChoicesList.push_back(currentPos);
		}
	}
	return positionChoicesList;
}

// ||
//((i == 2 || i == 3) && !(piecesBuffer.hasPiece(currentPos, (getSide() == Side::Black) ? Side::White : Side::Black))))