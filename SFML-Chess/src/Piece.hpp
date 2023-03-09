#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Piece
{
public:
	enum class Type
	{
		Blank = -1,
		King,
		Queen,
		Bishop,
		Knight,
		Rook,
		Pawn
	};

	enum class Side
	{
		White,
		Black
	};

	Piece(Type type, Side side);
	void setSpritePos(sf::Vector2i boardPos);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	Side mSide;
};