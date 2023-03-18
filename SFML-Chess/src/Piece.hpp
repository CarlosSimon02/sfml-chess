#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <memory>

#include "Board.hpp"
#include "PiecesBuffer.hpp"

class Piece
{
public:
	struct MoveDir
	{
		sf::Vector2i dir;
		uint16_t range;
	};

	Piece(const Type& type, const Side& side, sf::Vector2i pos, const std::vector<MoveDir>& moveDirs);
	void setPos(const sf::Vector2i& pos);
	sf::Sprite getSprite() const;
	sf::Vector2i getPos() const;
	virtual std::vector<sf::Vector2i> validPosList(PiecesBuffer& buff);
	std::vector<MoveDir>& getMoveDirs();
	Side getSide() const;
	Type getType() const;
	void setState(State state);
	State getState() const;
	virtual bool isValidPos(sf::Vector2i pos, PiecesBuffer& buff);
	bool isInMoveDirs(sf::Vector2i dir);
	virtual bool canBeReach(sf::Vector2i pos, PiecesBuffer& buff);

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	Type mType;
	Side mSide;
	State mState = State::Static;
	std::vector<MoveDir> mMoveDirs;

};