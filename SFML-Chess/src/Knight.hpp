#include <Piece.hpp>

class Knight : public Piece
{
public:
	Knight(Side side, const sf::Vector2i& position);
	std::vector<sf::Vector2i> createPositionChoices(PiecesBuffer& piecesBuffer) override;
};