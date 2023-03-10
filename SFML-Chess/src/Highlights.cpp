#include "Highlights.hpp"

void Highlights::setSquares(const std::vector<sf::Vector2i>& positions)
{
	clear();
	for (size_t i = 0; i < positions.size(); i++)
	{
		sf::RectangleShape square({ (float)Board::TILESIZE, (float)Board::TILESIZE });
		square.setPosition((float)(positions[i].x * Board::TILESIZE), (float)(positions[i].y * Board::TILESIZE));
		square.setFillColor((i == 0) ? mCurrentPositionColor : mOtherPositionColor);
		mSquares.push_back(square);
	}
}

void Highlights::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < mSquares.size(); i++)
		window.draw(mSquares[i]);
}

void Highlights::clear()
{
	mSquares.clear();
}
