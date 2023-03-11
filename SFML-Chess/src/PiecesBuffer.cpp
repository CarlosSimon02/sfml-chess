#include "PiecesBuffer.hpp"

PiecesBuffer::PiecesBuffer()
{
	std::array<int, 64> boardSetUp =
	{ 41, 31, 21, 11, 01, 21, 31, 41,
	  51, 51, 51, 51, 51, 51, 51, 51,
	  -10, -10, -10, -10, -10, -10, -10, -10,
	  -10, -10, -10, -10, -10, -10, -10, -10,
	  50, -10, -10, -10, -10, -10, -10, -10,
	  -10, -10, -10, -10, -10, -10, -10, -10,
	  50, 50, 50, 50, 50, 50, 50, 50,
	  40, 30, 20, 10, 00, 20, 30, 40 };


	for (size_t i = 0; i < mBuffer.size(); i++)
	{
		switch (static_cast<Piece::Type>(boardSetUp[i] / 10))
		{
		case Piece::Type::Blank:
			mBuffer[i] = nullptr;
			break;
		case Piece::Type::King:
			mBuffer[i].reset(new King(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Queen:
			mBuffer[i].reset(new Queen(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Bishop:
			mBuffer[i].reset(new Bishop(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Knight:
			mBuffer[i].reset(new Knight(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Rook:
			mBuffer[i].reset(new Rook(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		case Piece::Type::Pawn:
			mBuffer[i].reset(new Pawn(static_cast<Piece::Side>(boardSetUp[i] % 10)));
			break;
		}
	}
}

void PiecesBuffer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < mBuffer.size(); i++)
	{
		if (mBuffer[i] != NULL)
		{
			mBuffer[i]->setPos(Board::getVectorPosition(i));
			target.draw(mBuffer[i]->getSprite());
		}
	}
}

void PiecesBuffer::movePiece(sf::Uint16 old, sf::Uint16 current)
{
	mBuffer[current] = std::move(mBuffer[old]);
	mBuffer[current]->setPos(Board::getVectorPosition(current));
}

std::unique_ptr<Piece>& PiecesBuffer::operator[](int index)
{
	return mBuffer[index];
}
