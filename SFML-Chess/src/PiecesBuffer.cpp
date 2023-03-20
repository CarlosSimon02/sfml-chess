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

	//Parse boardSetup
	for (size_t i = 0; i < mBuffer.size(); i++)
	{
		switch (static_cast<Type>(boardSetUp[i] / 10))
		{
		case Type::Blank:
			mBuffer[i] = nullptr;
			break;
		case Type::King:
			mBuffer[i].reset(new King(static_cast<Side>(boardSetUp[i] % 10), Board::getVecPos((uint16_t)i)));
			break;
		case Type::Queen:
			mBuffer[i].reset(new Queen(static_cast<Side>(boardSetUp[i] % 10), Board::getVecPos((uint16_t)i)));
			break;
		case Type::Bishop:
			mBuffer[i].reset(new Bishop(static_cast<Side>(boardSetUp[i] % 10), Board::getVecPos((uint16_t)i)));
			break;
		case Type::Knight:
			mBuffer[i].reset(new Knight(static_cast<Side>(boardSetUp[i] % 10), Board::getVecPos((uint16_t)i)));
			break;
		case Type::Rook:
			mBuffer[i].reset(new Rook(static_cast<Side>(boardSetUp[i] % 10), Board::getVecPos((uint16_t)i)));
			break;
		case Type::Pawn:
			mBuffer[i].reset(new Pawn(static_cast<Side>(boardSetUp[i] % 10), Board::getVecPos((uint16_t)i)));
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

void PiecesBuffer::movePiece(uint16_t old, uint16_t current)
{
	mBuffer[current] = std::move(mBuffer[old]);
	mBuffer[current]->setPos(Board::getVecPos(current), *this);
	mBuffer[current]->setState(State::Moved);

	mLastMovedPiecePos = Board::getVecPos(current);
}

bool PiecesBuffer::hasPiece(sf::Vector2i position, Side side, Type type, State state)
{
	uint16_t bufferPos = Board::getBufPos(position);

	if (Board::posIsOOB(position) || mBuffer[bufferPos] == nullptr) return false;

	if (side == Side::Any || side == mBuffer[bufferPos]->getSide() &&
		type == Type::Any || type == mBuffer[bufferPos]->getType() &&
		state == State::Null || state == mBuffer[bufferPos]->getState()) return true;

	return false;
}

std::unique_ptr<Piece>& PiecesBuffer::operator[](int index)
{
	return mBuffer[index];
}

Side PiecesBuffer::getPlygSide() const
{
	return mPlayingSide;
}

void PiecesBuffer::setPlygSide(Side side)
{
	mPlayingSide = side;
}

sf::Vector2i PiecesBuffer::getLastMovedPiecePos() const
{
	return mLastMovedPiecePos;
}

bool PiecesBuffer::testCheck(sf::Vector2i old, sf::Vector2i current, Side side)
{
	if (old == current) return isInChk(side);

	std::unique_ptr<Piece> pieceHolder = nullptr;
	pieceHolder = std::move(mBuffer[Board::getBufPos(current)]);
	mBuffer[Board::getBufPos(current)] = std::move(mBuffer[Board::getBufPos(old)]);

	bool result = isInChk(side);

	mBuffer[Board::getBufPos(old)] = std::move(mBuffer[Board::getBufPos(current)]);
	mBuffer[Board::getBufPos(current)] = std::move(pieceHolder);

	return result;
}

bool PiecesBuffer::isInChk(Side side)
{
	for (std::unique_ptr<Piece>& piece : mBuffer)
	{
		if (piece != nullptr &&
			piece->getSide() != side &&
			piece->getSide() != mPlayingSide)
			for (sf::Vector2i validPos : piece->validPosList(*this))
				if (getPiecesPosByType(Type::King, side).size() > 0 &&
					getPiecesPosByType(Type::King, side)[0] == validPos)
					return true;
	}
	return false;
}

void PiecesBuffer::setCheckMateStat()
{
	if (isInChk(mPlayingSide) && mIsStaleMate)
	{
		mIsCheckMate = true;
		return;
	}
	mIsCheckMate = false;
}

bool PiecesBuffer::getCheckMateStat() const
{
	if (mIsCheckMate) std::cout << "Checkmate, " << ((mPlayingSide == Side::Black) ? "white " : "black ") << "won!" << std::endl;
	return mIsCheckMate;
}

void PiecesBuffer::setStaleMateStat()
{
	for (std::unique_ptr<Piece>& piece : mBuffer)
	{
		if (piece != nullptr &&
			piece->getSide() == mPlayingSide &&
			piece->validPosList(*this).size() > 1)
		{
			mIsStaleMate = false;
			return;
		}

	}
	mIsStaleMate = true;
}

bool PiecesBuffer::getStaleMateStat() const
{
	if (mIsStaleMate) std::cout << "stalemate" << std::endl;
	return mIsStaleMate;
}

void PiecesBuffer::setPromotingStat(bool stat)
{
	mIsPromoting = stat;
}

bool PiecesBuffer::getPromotingStat() const
{
	return mIsPromoting;
}

void PiecesBuffer::promote(sf::Vector2i pos, Type type)
{
	Side tempSide = mBuffer[Board::getBufPos(pos)]->getSide();

	switch (type)
	{
	case Type::Queen:
		mBuffer[Board::getBufPos(pos)].reset(new Queen(tempSide, pos));
		break;
	case Type::Bishop:
		mBuffer[Board::getBufPos(pos)].reset(new Bishop(tempSide, pos));
		break;
	case Type::Knight:
		mBuffer[Board::getBufPos(pos)].reset(new Knight(tempSide, pos));
		break;
	case Type::Rook:
		mBuffer[Board::getBufPos(pos)].reset(new Rook(tempSide, pos));
		break;
	}
}

std::vector<sf::Vector2i> PiecesBuffer::getPiecesPosByType(Type type, Side side)
{
	std::vector<sf::Vector2i> pieces;

	for (size_t i = 0; i < mBuffer.size(); i++)
	{
		if (mBuffer[i] != nullptr &&
			mBuffer[i]->getType() == type &&
			(side == Side::Any || mBuffer[i]->getSide() == side))
			pieces.push_back(Board::getVecPos((int)i));
	}
	return pieces;
}

