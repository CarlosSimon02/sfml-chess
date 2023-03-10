#include <Knight.hpp>

Knight::Knight(Side side)
	: Piece(Type::Knight, side,
		{ {-2,-1}, {+2,-1},{+2,+1},{-2,+1},    // L
		  {-1,-2}, {+1,-2},{+1,+2},{-1,+2} })
{}