#pragma once

#include <Piece.hpp>

class King : public Piece
{
public:
	King(Side side);
	std::vector<sf::Vector2i> createPositionChoices(std::array<std::unique_ptr<Piece>, 64>& piecesBuffer) override;

};