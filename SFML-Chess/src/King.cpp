#include <King.hpp>

#include <numeric>

King::King(Side side, sf::Vector2i position)
	: Piece(Type::King, side, position,
		{
			{ {-1,-1}, 1 }, //slant
			{ { 1,-1}, 1 },
			{ { 1, 1}, 1 },
			{ {-1, 1}, 1 },
			{ {-1, 0}, 3 }, //straight   //for castling queenside
			{ { 1, 0}, 2 },              //for castling kingside
			{ { 0, 1}, 1 },
			{ { 0,-1}, 1 }
		})
{}

std::vector<sf::Vector2i> King::validPosList(PiecesBuffer& buff)
{
	setCastlePos(buff);
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());
	for (const MoveDir& movedir : getMoveDirs())
		for (size_t j = 1; j <= movedir.range; j++)
			if (isValidPos({ getPos() + (movedir.dir * (int)j) }, buff))
				positionChoicesList.push_back({ getPos() + (movedir.dir * (int)j) });
	return positionChoicesList;
}

bool King::canBeReach(sf::Vector2i pos, PiecesBuffer& buff)
{
	sf::Vector2i dir = ((pos - getPos()) / std::gcd(pos.x - getPos().x, pos.y - getPos().y));
	for (sf::Vector2i i{ getPos() + dir }; i != pos; i += dir)
		if (buff.hasPiece(i) && buff.testCheck(getPos(),i, getSide()) && isInMoveDirs(dir))
			return false;
	return true;
}

void King::setPos(const sf::Vector2i& pos, PiecesBuffer& buff)
{
		if (pos == sf::Vector2i{ getPos() + (getMoveDirs()[4].dir * 2) })
		{
			sf::Vector2i qRookPos = (getSide() == Side::Black) ? sf::Vector2i{ 0,0 } : sf::Vector2i{ 0,7 };
			buff.movePiece(Board::getBufPos(qRookPos), Board::getBufPos({ qRookPos + sf::Vector2i{ 3,0 } }));
		}
		else if (pos == sf::Vector2i{ getPos() + (getMoveDirs()[5].dir * 2) })
		{
			sf::Vector2i kRookPos = (getSide() == Side::Black) ? sf::Vector2i{ 7,0 } : sf::Vector2i{ 7,7 };
			buff.movePiece(Board::getBufPos(kRookPos), Board::getBufPos({ kRookPos + sf::Vector2i{ -2,0 } }));
		}

		setLastMoveDirUsed(pos);
		setSpritePos(pos);
}

void King::setCastlePos(PiecesBuffer& buff)
{
	sf::Vector2i qRookOriginPos = { (getSide() == Side::Black) ? sf::Vector2i{0,0} : sf::Vector2i{0,7} };
	sf::Vector2i kRookOriginPos = { (getSide() == Side::Black) ? sf::Vector2i{7,0} : sf::Vector2i{7,7} };

	getMoveDirs()[4].range = 3;
	getMoveDirs()[5].range = 2;

	auto setCastle = [&](int index, sf::Vector2i rookPos)
	{
		for (size_t i = 0; i < getMoveDirs()[index].range; i++)
			if (getState() == State::Static &&
				buff.hasPiece(rookPos, getSide(), Type::Rook, State::Static) &&
				isValidPos(getPos() + getMoveDirs()[index].dir, buff) &&
				!buff.isInChk(getSide()))
			{
				getMoveDirs()[index].range = 2;
				return;
			}
		getMoveDirs()[index].range = 1;
		return;
	};
	setCastle(4, qRookOriginPos);
	setCastle(5, kRookOriginPos);
}

