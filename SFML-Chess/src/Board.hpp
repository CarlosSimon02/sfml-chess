#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum class Type
{
	Any = -2,
	Blank,
	King,
	Queen,
	Bishop,
	Knight,
	Rook,
	Pawn
};

enum class Side
{
	Any = -1,
	White,
	Black
};

enum class State
{
	Null,
	Moved,
	Static
};

class Board : public sf::Drawable
{
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	static bool posIsOOB(sf::Vector2i pos);
	static sf::Uint16 getBufPos(const sf::Vector2i position);
	static sf::Vector2i getVecPos(const sf::Uint16 bufferPosition);

	static const int TILESIZE;
	static const sf::Vector2i TILECOUNT;
	static const sf::Vector2i DIM;
};