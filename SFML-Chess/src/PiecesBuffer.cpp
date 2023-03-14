#include "PiecesBuffer.hpp"

#include "Piece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include "Pawn.hpp"

PiecesBuffer::PiecesBuffer()
{
	std::array<int, 64> boardSetUp =
	{  
	   41,  31,  21,  11,  01,  21,  31,  41,
	   51,  51,  51,  51,  51,  51,  51,  51,
	  -10, -10, -10, -10, -10, -10, -10, -10,
	  -10, -10, -10, -10, -10, -10, -10, -10,
	  -10, -10, -10, -10, -10, -10, -10, -10,
	  -10, -10, -10, -10, -10, -10, -10, -10,
	   50,  50,  50,  50,  50,  50,  50,  50,
	   40,  30,  20,  10,  00,  20,  30,  40 
	};


	for (size_t i = 0; i < mBuffer.size(); i++)
	{
		switch (static_cast<Type>(boardSetUp[i] / 10))
		{
		case Type::Blank:
			mBuffer[i] = nullptr;
			break;
		case Type::King:
			mBuffer[i].reset(new King(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((sf::Uint16)i)));
			break;
		case Type::Queen:
			mBuffer[i].reset(new Queen(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((sf::Uint16)i)));
			break;
		case Type::Bishop:
			mBuffer[i].reset(new Bishop(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((sf::Uint16)i)));
			break;
		case Type::Knight:
			mBuffer[i].reset(new Knight(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((sf::Uint16)i)));
			break;
		case Type::Rook:
			mBuffer[i].reset(new Rook(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((sf::Uint16)i)));
			break;
		case Type::Pawn:
			mBuffer[i].reset(new Pawn(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((sf::Uint16)i)));
			break;
		}
	}
}

void PiecesBuffer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < mBuffer.size(); i++)
	{
		if (mBuffer[i] != nullptr)
			target.draw(mBuffer[i]->getSprite());
	}
}

void PiecesBuffer::movePiece(sf::Uint16 old, sf::Uint16 current)
{
	mBuffer[current] = std::move(mBuffer[old]);
	mBuffer[current]->setPos(Board::getVectorPosition(current));
	mBuffer[current]->setState(State::Moved);
}

bool PiecesBuffer::hasPiece(sf::Vector2i position, Side side, Type type, State state)
{
	sf::Uint16 bufferPos = Board::getBufferPosition(position);

	if (Board::posIsOutOfBounds(position)) return false;

	if (mBuffer[bufferPos] == nullptr) return false;

	if (side == Side::Any || side == mBuffer[bufferPos]->getSide() &&
		type == Type::Any || type == mBuffer[bufferPos]->getType() &&
		state == State::Null || state == mBuffer[bufferPos]->getState()) return true;

	return false;
}

std::unique_ptr<Piece>& PiecesBuffer::operator[](int index)
{
	return mBuffer[index];
}

Side PiecesBuffer::getTurnSide() const
{
	return mTurnSide;
}

void PiecesBuffer::setTurnSide(Side side)
{
	mTurnSide = side;
}

const std::array<std::unique_ptr<Piece>, 64>& PiecesBuffer::get() const
{
	return mBuffer;
}
