#pragma once

#include <Piece.hpp>

class Rook : public Piece
{
public:
	Rook(Side side);
	std::vector<sf::Vector2i> createPositionChoices(std::array<std::unique_ptr<Piece>, 64>& piecesBuffer) override;
};