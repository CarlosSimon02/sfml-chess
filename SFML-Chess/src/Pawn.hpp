#pragma once

#include <Piece.hpp>

class Pawn : public Piece
{
public:
	Pawn(Side side);
	std::vector<sf::Vector2i> createPositionChoices(std::array<std::unique_ptr<Piece>, 64>& piecesBuffer) override;

private:
	bool mCanCapture;
	bool mCanEnpassant;
};