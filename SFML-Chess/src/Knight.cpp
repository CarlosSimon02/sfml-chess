#include <Knight.hpp>

Knight::Knight(Side side, const sf::Vector2i& position)
	: Piece(Type::Knight, side, position,
		{ {-2,-1}, {+2,-1},{+2,+1},{-2,+1},    // L
		  {-1,-2}, {+1,-2},{+1,+2},{-1,+2} })
{}

std::vector<sf::Vector2i> Knight::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	auto posAt = [&](int index) {return sf::Vector2i{ getPos().x + getMoveDirections()[index].x, getPos().y + getMoveDirections()[index].y }; };
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());
	for (size_t i = 0; i < getMoveDirections().size(); i++)
	{
		if (!Board::posIsOutOfBounds(posAt((int)i)) &&
			!piecesBuffer.hasPiece(posAt((int)i), getSide())) positionChoicesList.push_back(posAt((int)i));
	}
	return positionChoicesList;
}
