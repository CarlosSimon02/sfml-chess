#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);

	static const sf::Uint16 TILESIZE;
	static const sf::Vector2i TILECOUNT;
	static const sf::Vector2i DIM;

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
};