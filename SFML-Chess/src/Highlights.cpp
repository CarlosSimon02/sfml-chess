#include "Highlights.hpp"

void Highlights::setPositions(const std::vector<sf::Vector2i>& positions)
{
	clear();
	mPositions = positions;
}

void Highlights::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < mPositions.size(); i++)
	{
		sf::RectangleShape square({ (float)Board::TILESIZE, (float)Board::TILESIZE });
		square.setPosition((float)(mPositions[i].x * Board::TILESIZE), (float)(mPositions[i].y * Board::TILESIZE));
		square.setFillColor((i == 0) ? mCurrentPositionColor : mOtherPositionColor);
		target.draw(square);
	}
}

bool Highlights::isInPositionChoices(const sf::Vector2i& pos)
{
	for (size_t i = 0; i < mPositions.size(); i++)
		if (pos == mPositions[i]) return true;
	return false;
}

void Highlights::clear()
{
	mPositions.clear();
}
