#pragma once

#include <Piece.hpp>

class Bishop : public Piece
{
public: 
	Bishop(Side side, const sf::Vector2i& position);
};