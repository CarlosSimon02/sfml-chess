#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <memory>

#include "Board.hpp"

class PiecesBuffer;

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
	sf::Sprite getSprite() const;
	sf::Vector2i getPos() const;
	virtual std::vector<sf::Vector2i> createPositionChoices(PiecesBuffer& piecesBuffer);
	std::vector<sf::Vector2i> getMoveDirections() const;
	Side getSide() const;

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2i mPos = {};
	Type mType;
	Side mSide;
	std::vector<sf::Vector2i> mMoveDirections;

};