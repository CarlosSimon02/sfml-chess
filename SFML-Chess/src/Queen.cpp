#include <Queen.hpp>

Queen::Queen(Side side)
	: Piece(Type::Queen,side,
		{ {-1,-1}, {+1,-1},{+1,+1},{-1,+1},     //slant
		  {-1,0}, {+1,0},{0,+1},{0,-1} })		//straigth})
{}

std::vector<sf::Vector2i> Queen::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());
	for (size_t i = 0; i < getMoveDirections().size(); i++)
	{
		int offset = 1;
		while (getPos().x + getMoveDirections()[i].x * offset >= 0 &&
			getPos().x + getMoveDirections()[i].x * offset < Board::TILESIZE &&
			getPos().y + getMoveDirections()[i].y * offset >= 0 &&
			getPos().y + getMoveDirections()[i].y * offset < Board::TILESIZE)
		{
			positionChoicesList.push_back({ getPos().x + getMoveDirections()[i].x * offset,getPos().y + getMoveDirections()[i].y * offset });
			offset++;
		}
	}
	return positionChoicesList;
}