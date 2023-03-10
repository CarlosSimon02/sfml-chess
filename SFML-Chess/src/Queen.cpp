#include <Queen.hpp>

Queen::Queen(Side side)
	: Piece(Type::Queen,side,
		{ {-1,-1}, {+1,-1},{+1,+1},{-1,+1},     //slant
		  {-1,0}, {+1,0},{0,+1},{0,-1} })		//straigth})
{}