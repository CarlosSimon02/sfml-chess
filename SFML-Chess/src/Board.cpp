#include <Board.hpp>

void Board::draw(sf::RenderWindow& window)
{
	sf::Color GRAY{ 128,128,128 };
	for (size_t i = 0; i < (size_t)(TILECOUNT.x * TILECOUNT.y); i++)
	{
		sf::RectangleShape tile{ {(float)TILESIZE, (float)TILESIZE} };
		tile.setPosition({ (float)(i % TILECOUNT.x) * TILESIZE,(float)(i / TILECOUNT.y) * TILESIZE });
		tile.setFillColor(((i % TILECOUNT.x) % 2 == 1 && (i / TILECOUNT.y) % 2 == 0 || (i % TILECOUNT.x) % 2 == 0 && (i / TILECOUNT.y) % 2 == 1) ? GRAY : sf::Color::White);
		window.draw(tile);
	}
}

sf::Uint16 Board::getBufferPosition(const sf::Vector2i position)
{
	return ((position.y / Board::TILESIZE) * Board::TILECOUNT.x) + position.x / Board::TILESIZE;
}

const sf::Uint16   Board::TILESIZE = 100;
const sf::Vector2i Board::TILECOUNT = { 8,8 };
const sf::Vector2i Board::DIM = { 800,800 };