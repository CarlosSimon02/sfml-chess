#pragma once

#include <SFML/Graphics.hpp>

#include <Board.hpp>

class PromoteOption : public sf::Drawable
{
public:
	PromoteOption();
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void setChosenType(Type type);
	Type getChosenType() const;
	void setSide(Side side);
	Side getSide() const;
	sf::Sprite getSprite() const;
	bool isHovering(sf::Vector2i mousePos);

private:
	sf::Texture mTexture;
	sf::RectangleShape mBg{ sf::Vector2f(Board::TILECOUNT * Board::TILESIZE) };
	sf::RectangleShape mFill{ sf::Vector2f{4,1} *(float)Board::TILESIZE };
	sf::RectangleShape mHoverFill{ sf::Vector2f{1,1} * (float)Board::TILESIZE };
	sf::Sprite mSpriteList;
	Side mSide = Side::Black;
	Type mChosenType = Type::Blank;
};