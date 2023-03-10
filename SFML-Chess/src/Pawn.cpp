#include <Pawn.hpp>

Pawn::Pawn(Side side)
	: Piece(Type::Pawn, side, (Side::Black == side) ?
	std::vector<sf::Vector2i>{ {0, 1}, { 0,2 }, { -1,1 }, { 1,1 } } :   
	std::vector<sf::Vector2i>{ {0, -1}, { 0,-2 }, { -1,-1 }, { 1,-1 } })
{}