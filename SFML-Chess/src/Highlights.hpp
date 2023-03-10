#pragma once

#include "Piece.hpp"

class Highlights
{
public:
	void setSquares(const std::vector<sf::Vector2i>& positions);
	void draw(sf::RenderWindow& window);
	void clear();

private:
	std::vector<sf::RectangleShape> mSquares;
	sf::Color mCurrentPositionColor = { 85,107,47,150 };
	sf::Color mOtherPositionColor = { 107,142,35,150 };
};