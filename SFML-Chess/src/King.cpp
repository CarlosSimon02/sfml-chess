#include <King.hpp>

King::King(Side side)
	: Piece(Type::King, side,
		{ {-1,-1}, {+1,-1},{+1,+1},{-1,+1},     //slant
		  {-1,0}, {+1,0},{0,+1},{0,-1},			//straigth
		  {-2,0}, {+2,0} })						//castling
{}

std::vector<sf::Vector2i> King::createPositionChoices(std::array<std::unique_ptr<Piece>, 64>& piecesBuffer)
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