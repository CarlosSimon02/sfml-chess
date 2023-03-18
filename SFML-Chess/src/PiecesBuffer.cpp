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
	checkForEnpassant(old,current);
	checkForCastle(old, current);

	mBuffer[current] = std::move(mBuffer[old]);
	mBuffer[current]->setPos(Board::getVecPos(current));
	mBuffer[current]->setState(State::Moved);
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

Side PiecesBuffer::getTurnSide() const
{
	return mTurnSide;
}

void PiecesBuffer::setTurnSide(Side side)
{
	mTurnSide = side;
}

std::pair<sf::Vector2i, sf::Vector2i> PiecesBuffer::getEnpassantPos() const
{
	return mCanEnpassantPos;
}

void PiecesBuffer::checkForEnpassant(uint16_t old, uint16_t current)
{
	//mCanEnpassantPos = { {-1,-1},{-1,-1} };
	if (mBuffer[old]->getType() == Type::Pawn)
	{
		if (Board::getVecPos(current) == sf::Vector2i{ mBuffer[old]->getPos() + (mBuffer[old]->getMoveDirs()[0].dir * 2) })
		{
			sf::Vector2i left = { Board::getVecPos(current) + sf::Vector2i{-1,0}};
			sf::Vector2i right = { Board::getVecPos(current) + sf::Vector2i{1,0} };
			if (!Board::posIsOOB(left)) mCanEnpassantPos.first = left;
			if (!Board::posIsOOB(right)) mCanEnpassantPos.second = right;
		}
		if (Board::getVecPos(current) == sf::Vector2i{ mBuffer[old]->getPos() + mBuffer[old]->getMoveDirs()[2].dir } && mCanEnpassantPos.first == mBuffer[old]->getPos() ||
			Board::getVecPos(current) == sf::Vector2i{ mBuffer[old]->getPos() + mBuffer[old]->getMoveDirs()[1].dir } && mCanEnpassantPos.second == mBuffer[old]->getPos())
		{
			mBuffer[Board::getBufPos({ Board::getVecPos(current) - mBuffer[old]->getMoveDirs()[0].dir })].reset();
		}
	}
}

void PiecesBuffer::checkForCastle(uint16_t old, uint16_t current)
{
	if (mBuffer[old]->getType() == Type::King)
	{
		if (Board::getVecPos(current) == sf::Vector2i{ mBuffer[old]->getPos() + (mBuffer[old]->getMoveDirs()[4].dir * 2) })
		{
			sf::Vector2i qRookPos = (mBuffer[old]->getSide() == Side::Black) ? sf::Vector2i{ 0,0 } : sf::Vector2i{ 0,7 };
			mBuffer[Board::getBufPos({ qRookPos + sf::Vector2i{3,0} })] = std::move(mBuffer[Board::getBufPos(qRookPos)]);
			mBuffer[Board::getBufPos({ qRookPos + sf::Vector2i{3,0} })]->setPos({ qRookPos + sf::Vector2i{3,0} });
			mBuffer[Board::getBufPos({ qRookPos + sf::Vector2i{3,0} })]->setState(State::Moved);
		}
		else if (Board::getVecPos(current) == sf::Vector2i{ mBuffer[old]->getPos() + (mBuffer[old]->getMoveDirs()[5].dir * 2) })
		{
			sf::Vector2i kRookPos = (mBuffer[old]->getSide() == Side::Black) ? sf::Vector2i{ 7,0 } : sf::Vector2i{ 7,7 };
			mBuffer[Board::getBufPos({ kRookPos - sf::Vector2i{2,0} })] = std::move(mBuffer[Board::getBufPos(kRookPos)]);
			mBuffer[Board::getBufPos({ kRookPos - sf::Vector2i{2,0} })]->setPos({ kRookPos - sf::Vector2i{2,0} });
			mBuffer[Board::getBufPos({ kRookPos - sf::Vector2i{2,0} })]->setState(State::Moved);
		}
	}
}

bool PiecesBuffer::testCheck(sf::Vector2i old, sf::Vector2i current, Side side)
{
	if (old == current) return kingIsInCheck(side);

	std::unique_ptr<Piece> pieceHolder = nullptr;
	pieceHolder = std::move(mBuffer[Board::getBufPos(current)]);
	mBuffer[Board::getBufPos(current)] = std::move(mBuffer[Board::getBufPos(old)]);

	bool result = kingIsInCheck(side);

	mBuffer[Board::getBufPos(old)] = std::move(mBuffer[Board::getBufPos(current)]);
	mBuffer[Board::getBufPos(current)] = std::move(pieceHolder);

	return result;
}

bool PiecesBuffer::kingIsInCheck(Side side)
{
	for (std::unique_ptr<Piece>& piece: mBuffer)
	{
		if (piece != nullptr &&
			piece->getSide() != side &&
			piece->getSide() != mTurnSide)
			for (sf::Vector2i validPos : piece->validPosList(*this))
				if (getPiecesPosByType(Type::King, side).size() > 0 &&
					getPiecesPosByType(Type::King, side)[0] == validPos)
					return true;
	}
	return false;
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

const std::array<std::unique_ptr<Piece>, 64>& PiecesBuffer::get() const
{
	return mBuffer;
}
