#include <Rook.hpp>

Rook::Rook(Side side, sf::Vector2i position)
	: Piece(Type::Rook, side, position,
		{
			{ {-1, 0}, (uint16_t)Board::TILECOUNT.x }, //straight   
			{ { 1, 0}, (uint16_t)Board::TILECOUNT.x },
			{ { 0, 1}, (uint16_t)Board::TILECOUNT.x },
			{ { 0,-1}, (uint16_t)Board::TILECOUNT.x }
		})
{}