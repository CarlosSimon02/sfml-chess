#include <Piece.hpp>

class Knight : public Piece
{
public:
	Knight(Side);
	std::vector<sf::Vector2i> createPositionChoices(std::array<std::unique_ptr<Piece>, 64>& piecesBuffer) override;
};