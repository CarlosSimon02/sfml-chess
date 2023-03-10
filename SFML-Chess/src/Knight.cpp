#include <Knight.hpp>

Knight::Knight(Side side)
	: Piece(Type::Knight, side,
		{ {-2,-1}, {+2,-1},{+2,+1},{-2,+1},    // L
		  {-1,-2}, {+1,-2},{+1,+2},{-1,+2} })
{}

std::vector<sf::Vector2i> Knight::createPositionChoices(std::array<std::unique_ptr<Piece>, 64>&piecesBuffer)
{
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());
	for (size_t i = 0; i < getMoveDirections().size(); i++)
	{
		if (getPos().x + getMoveDirections()[i].x < 0 ||
			getPos().x + getMoveDirections()[i].x >= Board::TILESIZE ||
			getPos().y + getMoveDirections()[i].y < 0 ||
			getPos().y + getMoveDirections()[i].y >= Board::TILESIZE) continue;
		positionChoicesList.push_back({ getPos().x + getMoveDirections()[i].x,getPos().y + getMoveDirections()[i].y });
	}
	return positionChoicesList;
}
