#pragma once 

#include <SFML/Graphics.hpp>

#include "Piece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include "Pawn.hpp"

class PiecesBuffer: public sf::Drawable
{
public:
	PiecesBuffer();
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void movePiece(sf::Uint16 old, sf::Uint16 current);
	std::unique_ptr<Piece>& operator[](int index);

private:
	std::array<std::unique_ptr<Piece>, 64> mBuffer;
};