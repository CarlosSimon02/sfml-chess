#include <Bishop.hpp>

Bishop::Bishop(Side side)
	: Piece(Type::Bishop, side,
		{ {-1,-1}, {+1,-1},{+1,+1},{-1,+1} })//slant
{}