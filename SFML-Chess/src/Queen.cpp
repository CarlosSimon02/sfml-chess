#include <Queen.hpp>

Queen::Queen(Side side, const sf::Vector2i& position)
	: Piece(Type::Queen,side, position,
		{ 
			{ {-1,-1}, (uint16_t)Board::TILECOUNT.x }, //slant
			{ { 1,-1}, (uint16_t)Board::TILECOUNT.x },
			{ { 1, 1}, (uint16_t)Board::TILECOUNT.x },
			{ {-1, 1}, (uint16_t)Board::TILECOUNT.x },
			{ {-1, 0}, (uint16_t)Board::TILECOUNT.x }, //straight   
			{ { 1, 0}, (uint16_t)Board::TILECOUNT.x },            
			{ { 0, 1}, (uint16_t)Board::TILECOUNT.x },
			{ { 0,-1}, (uint16_t)Board::TILECOUNT.x }
		})
{}