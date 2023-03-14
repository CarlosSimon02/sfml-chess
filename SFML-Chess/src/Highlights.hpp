#pragma once

#include "Piece.hpp"

class Highlights : public sf::Drawable
{
public:
	void setPositions(const std::vector<sf::Vector2i>& positions);
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	bool isInPositionChoices(const sf::Vector2i& pos);
	void clear();

private:
	std::vector<sf::Vector2i> mPositions;
	sf::Color mCurrentPositionColor = { 85,107,47,150 };
	sf::Color mOtherPositionColor = { 107,142,35,150 };
};