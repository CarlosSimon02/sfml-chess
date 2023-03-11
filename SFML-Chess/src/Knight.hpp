#include <Piece.hpp>

class Knight : public Piece
{
public:
	Knight(Side);
	std::vector<sf::Vector2i> createPositionChoices(PiecesBuffer& piecesBuffer) override;
};