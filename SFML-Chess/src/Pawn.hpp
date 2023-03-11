#pragma once

#include <Piece.hpp>

class Pawn : public Piece
{
public:
	Pawn(Side side);
	std::vector<sf::Vector2i> createPositionChoices(PiecesBuffer& piecesBuffer) override;

private:
	bool mCanCapture;
	bool mCanEnpassant;
};