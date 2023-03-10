#include <King.hpp>

King::King(Side side)
	: Piece(Type::King, side,
		{ {-1,-1}, {+1,-1},{+1,+1},{-1,+1},     //slant
		  {-1,0}, {+1,0},{0,+1},{0,-1},			//straigth
		  {-3,0}, {+2,0} })						//castling
{}