#include <King.hpp>

King::King(Side side, const sf::Vector2i& position)
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

std::vector<sf::Vector2i> King::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());

	sf::Vector2i qRookOriginPos = { (getSide() == Side::Black) ? sf::Vector2i{0,0} : sf::Vector2i{0,7} };
	sf::Vector2i kRookOriginPos = { (getSide() == Side::Black) ? sf::Vector2i{7,0} : sf::Vector2i{7,7} };

	getMoveDirs()[4].range = 3;
	getMoveDirs()[5].range = 2;

	auto setCastle = [&](int index, sf::Vector2i rookPos)
	{
		for (size_t i = 0; i < getMoveDirs()[index].range; i++)
			if (getState() == State::Moved ||
				!piecesBuffer.hasPiece(rookPos, getSide(), Type::Rook, State::Static) ||
				piecesBuffer.kingIsInCheck(getPos(), getPos(), getSide()) ||
				piecesBuffer.hasPiece({ getPos().x + getMoveDirs()[index].dir.x,getPos().y + getMoveDirs()[index].dir.y }))
			{
				getMoveDirs()[index].range = 1;
				return;
			}

		getMoveDirs()[index].range = 2;
		return;
	};

	setCastle(4, qRookOriginPos);
	setCastle(5, kRookOriginPos);


	for (size_t i = 0; i < getMoveDirs().size(); i++)
	{
		for (size_t j = 1;
			j <= getMoveDirs()[i].range &&
			!Board::posIsOutOfBounds({ getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }) &&
			!piecesBuffer.hasPiece({ getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }, getSide()) &&
			!piecesBuffer.kingIsInCheck(getPos(), { getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j }, getSide());
			j++)
		{
			sf::Vector2i currentPos = { getPos().x + getMoveDirs()[i].dir.x * (int)j, getPos().y + getMoveDirs()[i].dir.y * (int)j };
			positionChoicesList.push_back(currentPos);

			if (piecesBuffer.hasPiece(currentPos, (getSide() == Side::Black) ? Side::White : Side::Black)) break;
		}
	}
	return positionChoicesList;
}

