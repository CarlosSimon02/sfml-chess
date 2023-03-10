#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Board
{
public:
	void draw(sf::RenderWindow& window);
	static sf::Uint16 getBufferPosition(const sf::Vector2i position);

	static const sf::Uint16 TILESIZE;
	static const sf::Vector2i TILECOUNT;
	static const sf::Vector2i DIM;
};