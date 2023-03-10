#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Board.hpp"

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

	Piece(const Type& type, const Side& side, const std::vector<sf::Vector2i>& moveDirections);
	void setPos(const sf::Vector2i& boardPos);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2i mPos = {};
	Type mType;
	Side mSide;
	std::vector<sf::Vector2i> mMoveDirections;
};