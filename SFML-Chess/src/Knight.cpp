#include <Knight.hpp>

Knight::Knight(Side side, const sf::Vector2i& position)
	: Piece(Type::Knight, side, position,
		{ 
			{{-2,-1}, 1}, //L
			{{ 2,-1}, 1},
			{{ 2, 1}, 1},
			{{-2, 1}, 1},   
			{{-1,-2}, 1}, 
			{{ 1,-2}, 1},
			{{ 1, 2}, 1},
			{{-1, 2}, 1} 
		})
{}