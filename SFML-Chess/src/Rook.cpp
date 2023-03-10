#include <Rook.hpp>

Rook::Rook(Side side)
	: Piece(Type::Rook, side,
		{ {-1,0}, {+1,0},{0,+1},{0,-1} }) //straight
{}