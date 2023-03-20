#include "Board.hpp"

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Color GRAY{ 128,128,128 };
	for (size_t i = 0; i < (size_t)(TILECOUNT.x * TILECOUNT.y); i++)
	{
		sf::RectangleShape tile{ {(float)TILESIZE, (float)TILESIZE} };
		tile.setPosition({ (float)(i % TILECOUNT.x) * TILESIZE,(float)(i / TILECOUNT.y) * TILESIZE });
		tile.setFillColor(((i % TILECOUNT.x) % 2 == 1 && (i / TILECOUNT.y) % 2 == 0 || (i % TILECOUNT.x) % 2 == 0 && (i / TILECOUNT.y) % 2 == 1) ? GRAY : sf::Color::White);
		target.draw(tile);
	}
}

bool Board::posIsOOB(sf::Vector2i pos)
{
	if (pos.x < 0 || pos.x >= Board::TILECOUNT.x ||
		pos.y < 0 || pos.y >= Board::TILECOUNT.y) return true;

	return false;
}

sf::Uint16 Board::getBufPos(const sf::Vector2i position)
{
	return ((position.y) * Board::TILECOUNT.x) + position.x;
}

sf::Vector2i Board::getVecPos(const sf::Uint16 bufferPosition)
{
	return sf::Vector2i{ bufferPosition % TILECOUNT.x, bufferPosition / TILECOUNT.y };
}

const int          Board::TILESIZE = 100;
const sf::Vector2i Board::TILECOUNT = { 8,8 };
const sf::Vector2i Board::DIM = { 800,800 };