#pragma once 

#include <SFML/Graphics.hpp>
#include <array>

#include <Board.hpp>

class Piece;

class PiecesBuffer: public sf::Drawable
{
public:
	PiecesBuffer();
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void movePiece(uint16_t old, uint16_t current);
	bool hasPiece(sf::Vector2i position, Side side = Side::Any, Type type = Type::Any, State state = State::Null);
	std::unique_ptr<Piece>& operator[](int index);
	Side getPlygSide() const;
	void setPlygSide(Side side);
	bool isInChk(Side side);
	std::vector<sf::Vector2i> getPiecesPosByType(Type type, Side side = Side::Any);
	bool testCheck(sf::Vector2i old, sf::Vector2i current, Side side);
	sf::Vector2i getLastMovedPiecePos() const;
	void setCheckMateStat();
	bool getCheckMateStat() const;
	void setStaleMateStat();
	bool getStaleMateStat() const;
	void setPromotingStat(bool stat);
	bool getPromotingStat() const;
	void promote(sf::Vector2i pos, Type type);
		
private:
	std::array<std::unique_ptr<Piece>, 64> mBuffer;
	Side mPlayingSide = Side::White;
	sf::Vector2i mLastMovedPiecePos;
	bool mIsStaleMate = false;
	bool mIsCheckMate = false;
	bool mIsPromoting = false;
};