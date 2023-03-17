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
			mBuffer[i].reset(new King(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((uint16_t)i)));
			break;
		case Type::Queen:
			mBuffer[i].reset(new Queen(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((uint16_t)i)));
			break;
		case Type::Bishop:
			mBuffer[i].reset(new Bishop(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((uint16_t)i)));
			break;
		case Type::Knight:
			mBuffer[i].reset(new Knight(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((uint16_t)i)));
			break;
		case Type::Rook:
			mBuffer[i].reset(new Rook(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((uint16_t)i)));
			break;
		case Type::Pawn:
			mBuffer[i].reset(new Pawn(static_cast<Side>(boardSetUp[i] % 10), Board::getVectorPosition((uint16_t)i)));
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
	//for castling
	if (mBuffer[old]->getType() == Type::King)
	{
		if (Board::getVectorPosition(current) == sf::Vector2i{ mBuffer[old]->getPos().x + mBuffer[old]->getMoveDirs()[4].dir.x * 2, mBuffer[old]->getPos().y + mBuffer[old]->getMoveDirs()[4].dir.y * 2})
		{
			sf::Vector2i qRookPos = (mBuffer[old]->getSide() == Side::Black) ? sf::Vector2i{ 0,0 } : sf::Vector2i{ 0,7 };
			mBuffer[Board::getBufferPosition({ qRookPos.x + 3,qRookPos.y })] = std::move(mBuffer[Board::getBufferPosition(qRookPos)]);
			mBuffer[Board::getBufferPosition({ qRookPos.x + 3,qRookPos.y })]->setPos({ qRookPos.x + 3,qRookPos.y });
			mBuffer[Board::getBufferPosition({ qRookPos.x + 3,qRookPos.y })]->setState(State::Moved);
		}
		else if (Board::getVectorPosition(current) == sf::Vector2i{ mBuffer[old]->getPos().x + mBuffer[old]->getMoveDirs()[5].dir.x * 2, mBuffer[old]->getPos().y + mBuffer[old]->getMoveDirs()[5].dir.y * 2 })
		{
			sf::Vector2i kRookPos = (mBuffer[old]->getSide() == Side::Black) ? sf::Vector2i{ 7,0 } : sf::Vector2i{ 7,7 };
			mBuffer[Board::getBufferPosition({ kRookPos.x - 2,kRookPos.y })] = std::move(mBuffer[Board::getBufferPosition(kRookPos)]);
			mBuffer[Board::getBufferPosition({ kRookPos.x - 2,kRookPos.y })]->setPos({ kRookPos.x - 2,kRookPos.y });
			mBuffer[Board::getBufferPosition({ kRookPos.x - 2,kRookPos.y })]->setState(State::Moved);
		}
	}

	//for enpassant
	mCanEnpassantPos = { {-1,-1},{-1,-1} };
	if (mBuffer[old]->getType() == Type::Pawn)
	{
		if (Board::getVectorPosition(current) == sf::Vector2i{ mBuffer[old]->getPos().x + mBuffer[old]->getMoveDirs()[0].dir.x * 2, mBuffer[old]->getPos().y + mBuffer[old]->getMoveDirs()[0].dir.y * 2 })
		{
			sf::Vector2i left = { Board::getVectorPosition(current).x - 1,Board::getVectorPosition(current).y };
			sf::Vector2i right = { Board::getVectorPosition(current).x + 1,Board::getVectorPosition(current).y };
			if (!Board::posIsOutOfBounds(left)) mCanEnpassantPos.first = left;
			if (!Board::posIsOutOfBounds(right)) mCanEnpassantPos.second = right;
		}
		if ((Board::getVectorPosition(current) == sf::Vector2i{ mBuffer[old]->getPos().x + mBuffer[old]->getMoveDirs()[2].dir.x, mBuffer[old]->getPos().y + mBuffer[old]->getMoveDirs()[2].dir.y }) ||
			Board::getVectorPosition(current) == sf::Vector2i{ mBuffer[old]->getPos().x + mBuffer[old]->getMoveDirs()[1].dir.x, mBuffer[old]->getPos().y + mBuffer[old]->getMoveDirs()[1].dir.y })
		{
			std::cout << "run" << std::endl;
			mBuffer[Board::getBufferPosition({ Board::getVectorPosition(current).x, Board::getVectorPosition(current).y - mBuffer[old]->getMoveDirs()[0].dir.y })].reset();
		}

	}

	mBuffer[current] = std::move(mBuffer[old]);
	mBuffer[current]->setPos(Board::getVectorPosition(current));
	mBuffer[current]->setState(State::Moved);



}

bool PiecesBuffer::hasPiece(sf::Vector2i position, Side side, Type type, State state)
{
	uint16_t bufferPos = Board::getBufferPosition(position);

	if (Board::posIsOutOfBounds(position) || mBuffer[bufferPos] == nullptr) return false;

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

bool PiecesBuffer::kingIsInCheck(const sf::Vector2i testOldPos, const sf::Vector2i& testNewPos, Side side)
{
	if (Board::posIsOutOfBounds(testNewPos)) return false;

	std::unique_ptr<Piece> pieceHolder = nullptr;

	if (testOldPos != testNewPos)
	{
		pieceHolder = std::move(mBuffer[Board::getBufferPosition(testNewPos)]);
		mBuffer[Board::getBufferPosition(testNewPos)] = std::move(mBuffer[Board::getBufferPosition(testOldPos)]);
	}

	for (size_t i = 0; i < mBuffer.size(); i++)
	{
		if (mBuffer[(int)i] != nullptr &&
			mBuffer[(int)i]->getSide() != side &&
			mBuffer[i]->getSide() != mTurnSide)
			for (size_t j = 1; j < mBuffer[(int)i]->createPositionChoices(*this).size(); j++)
				if (getPiecesPosByType(Type::King, side).size() > 0 && getPiecesPosByType(Type::King, side)[0] == mBuffer[(int)i]->createPositionChoices(*this)[(int)j])
				{
					if (testOldPos != testNewPos)
					{
						mBuffer[Board::getBufferPosition(testOldPos)] = std::move(mBuffer[Board::getBufferPosition(testNewPos)]);
						mBuffer[Board::getBufferPosition(testNewPos)] = std::move(pieceHolder);
					}
					return true;
				}
	}

	if (testOldPos != testNewPos)
	{
		mBuffer[Board::getBufferPosition(testOldPos)] = std::move(mBuffer[Board::getBufferPosition(testNewPos)]);
		mBuffer[Board::getBufferPosition(testNewPos)] = std::move(pieceHolder);
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
			pieces.push_back(Board::getVectorPosition((int)i));
	}
	return pieces;
}

const std::array<std::unique_ptr<Piece>, 64>& PiecesBuffer::get() const
{
	return mBuffer;
}
