#pragma once

#include <Piece.hpp>

class Pawn : public Piece
{
public:
	Pawn(Side side, sf::Vector2i position);
	std::vector<sf::Vector2i> validPosList(PiecesBuffer& piecesBuffer) override;
	bool isValidPos(sf::Vector2i pos, PiecesBuffer& buff) override;
	void setPos(const sf::Vector2i& pos, PiecesBuffer& buff) override;
};