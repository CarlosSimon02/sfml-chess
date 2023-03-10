#pragma once

#include <Piece.hpp>

class Queen : public Piece
{
public:
	Queen(Side side);
	std::vector<sf::Vector2i> createPositionChoices(std::array<std::unique_ptr<Piece>, 64>& piecesBuffer) override;
};