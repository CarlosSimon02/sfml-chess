#include <Bishop.hpp>

Bishop::Bishop(Side side, sf::Vector2i position)
	: Piece(Type::Bishop, side, position,
		{
			{ {-1,-1}, (uint16_t)Board::TILECOUNT.x }, //slant
			{ { 1,-1}, (uint16_t)Board::TILECOUNT.x },
			{ { 1, 1}, (uint16_t)Board::TILECOUNT.x },
			{ {-1, 1}, (uint16_t)Board::TILECOUNT.x }
		})
{}

