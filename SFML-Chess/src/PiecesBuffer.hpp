#pragma once 

#include <SFML/Graphics.hpp>
#include <array>

class Piece;

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

class PiecesBuffer: public sf::Drawable
{
public:
	PiecesBuffer();
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void movePiece(uint16_t old, uint16_t current);
	bool hasPiece(sf::Vector2i position, Side side = Side::Any, Type type = Type::Any, State state = State::Null);
	std::unique_ptr<Piece>& operator[](int index);
	const std::array<std::unique_ptr<Piece>, 64>& get() const;
	Side getTurnSide() const;
	void setTurnSide(Side side);
	bool kingIsInCheck(Side side);
	std::vector<sf::Vector2i> getPiecesPosByType(Type type, Side side = Side::Any);
	std::pair<sf::Vector2i, sf::Vector2i> getEnpassantPos() const;
	bool testCheck(sf::Vector2i old, sf::Vector2i current, Side side);

private:
	void checkForCastle(uint16_t old, uint16_t current);
	void checkForEnpassant(uint16_t old, uint16_t current);
		
private:
	std::array<std::unique_ptr<Piece>, 64> mBuffer;
	Side mTurnSide = Side::White;
	std::pair<sf::Vector2i, sf::Vector2i> mCanEnpassantPos = { {-1,-1},{-1,-1} };
};