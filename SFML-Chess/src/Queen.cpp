#include <Queen.hpp>

Queen::Queen(Side side, const sf::Vector2i& position)
	: Piece(Type::Queen,side, position,
		{ {-1,-1}, {+1,-1},{+1,+1},{-1,+1},     //slant
		  {-1,0}, {+1,0},{0,+1},{0,-1} })		//straigth})
{}

std::vector<sf::Vector2i> Queen::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	auto posAt = [&](int index, int offset) {return sf::Vector2i{ getPos().x + getMoveDirections()[index].x * offset, getPos().y + getMoveDirections()[index].y * offset }; };
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());
	for (size_t i = 0; i < getMoveDirections().size(); i++)
	{
		int offset = 1;
		while (!Board::posIsOutOfBounds(posAt((int)i, offset)) &&
			!piecesBuffer.hasPiece(posAt((int)i, offset), getSide()))
		{
			positionChoicesList.push_back(posAt((int)i, offset));
			if (piecesBuffer.hasPiece(posAt((int)i, offset), (getSide() == Side::Black) ? Side::White : Side::Black) &&
				!piecesBuffer.hasPiece(posAt((int)i, offset), (getSide() == Side::Black) ? Side::White : Side::Black, Type::King)) break;
			offset++;
		}
	}
	return positionChoicesList;
}