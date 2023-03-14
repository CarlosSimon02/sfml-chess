#include <King.hpp>

King::King(Side side, const sf::Vector2i& position)
	: Piece(Type::King, side, position,
		{ {-1,-1}, {+1,-1},{+1,+1},{-1,+1},     //slant
		  {-1,0}, {+1,0},{0,+1},{0,-1},			//straigth
		  {-2,0}, {+2,0}, {-3,0} })				//castling
{}

std::vector<sf::Vector2i> King::createPositionChoices(PiecesBuffer& piecesBuffer)
{
	auto posAt = [&](int index) {return sf::Vector2i{ getPos().x + getMoveDirections()[index].x, getPos().y + getMoveDirections()[index].y }; };
	std::vector<sf::Vector2i> positionChoicesList;
	positionChoicesList.push_back(getPos());

	sf::Vector2i qRookOriginPos = { (getSide() == Side::Black) ? sf::Vector2i{0,0} : sf::Vector2i{0,7} };
	sf::Vector2i kRookOriginPos = { (getSide() == Side::Black) ? sf::Vector2i{7,0} : sf::Vector2i{7,7} };

	for (size_t i = 0; i < getMoveDirections().size() - 1; i++)
	{
		if (!Board::posIsOutOfBounds(posAt((int)i)) &&
			!piecesBuffer.hasPiece(posAt((int)i), getSide()) &&
			!isInCheck(posAt((int)i), piecesBuffer)) 
		{
			if ((i == 8 && (isInCheck(posAt(4), piecesBuffer) || piecesBuffer.hasPiece(posAt(4)) || isInCheck(posAt(10), piecesBuffer) || piecesBuffer.hasPiece(posAt(10)) || !piecesBuffer.hasPiece(qRookOriginPos, getSide(), Type::Rook, State::Static) || getState() == State::Moved)) ||
				(i == 9 && (isInCheck(posAt(5), piecesBuffer) || piecesBuffer.hasPiece(posAt(5)) || !piecesBuffer.hasPiece(kRookOriginPos, getSide(), Type::Rook, State::Static) || getState() == State::Moved)))
				continue;
			positionChoicesList.push_back(posAt((int)i));
		}
	}
	return positionChoicesList;
}

bool King::isInCheck(sf::Vector2i pos, PiecesBuffer& piecesBuffer)
{
	for (size_t i = 0; i < piecesBuffer.get().size(); i++)
	{
		if (piecesBuffer[(int)i] != nullptr && piecesBuffer.getTurnSide() == getSide())
		{
			if (piecesBuffer[(int)i]->getSide() == ((getSide() == Side::Black) ? Side::White : Side::Black))
				for (size_t j = 0; j < piecesBuffer[(int)i]->createPositionChoices(piecesBuffer).size(); j++)
					if (pos == piecesBuffer[(int)i]->createPositionChoices(piecesBuffer)[(int)j]) return true;
		}
	}

	return false;
}
