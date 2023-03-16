#pragma once

#include <Piece.hpp>

class Rook : public Piece
{
public:
	Rook(Side side, const sf::Vector2i& position);
};