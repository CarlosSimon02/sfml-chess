#pragma once

#include <Piece.hpp>

class King : public Piece
{
public:
	King(Side side,  sf::Vector2i position);
	std::vector<sf::Vector2i> validPosList(PiecesBuffer& piecesBuffer) override;
	bool canBeReach(sf::Vector2i pos, PiecesBuffer& buff) override;

private:
	void setCastlePos(PiecesBuffer& buff);
};