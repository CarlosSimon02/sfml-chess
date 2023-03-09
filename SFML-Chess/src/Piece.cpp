#include "Piece.hpp"

Piece::Piece(Type type, Side side)
	: mSide(side)
{
	mTexture.loadFromFile("assets/chess-pieces.png");
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect({ static_cast<int>(type) * 100,static_cast<int>(side) * 100, 100,100 });
}

void Piece::setSpritePos(sf::Vector2i boardPos)
{
	mSprite.setPosition(sf::Vector2f(boardPos.x * 100, boardPos.y * 100));
}

void Piece::draw(sf::RenderWindow& window)
{
	window.draw(mSprite);
}
