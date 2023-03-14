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
	void movePiece(sf::Uint16 old, sf::Uint16 current);
	bool hasPiece(sf::Vector2i position, Side side = Side::Any, Type type = Type::Any, State state = State::Null);
	std::unique_ptr<Piece>& operator[](int index);
	const std::array<std::unique_ptr<Piece>, 64>& get() const;
	Side getTurnSide() const;
	void setTurnSide(Side side);

private:
	std::array<std::unique_ptr<Piece>, 64> mBuffer;
	Side mTurnSide = Side::White;
};