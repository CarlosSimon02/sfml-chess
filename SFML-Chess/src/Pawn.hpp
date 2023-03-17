#pragma once

#include <Piece.hpp>

class Pawn : public Piece
{
public:
	Pawn(Side side, const sf::Vector2i& position);
	std::vector<sf::Vector2i> createPositionChoices(PiecesBuffer& piecesBuffer) override;
};