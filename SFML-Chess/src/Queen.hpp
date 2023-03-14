#pragma once

#include <Piece.hpp>

class Queen : public Piece
{
public:
	Queen(Side side, const sf::Vector2i& position);
	std::vector<sf::Vector2i> createPositionChoices(PiecesBuffer& piecesBuffer) override;
};