#pragma once

#include <Piece.hpp>

class Rook : public Piece
{
public:
	Rook(Side side);
	std::vector<sf::Vector2i> createPositionChoices(PiecesBuffer& piecesBuffer) override;
};