#include "PromoteOption.hpp"

PromoteOption::PromoteOption()
{
	mBg.setFillColor(sf::Color(105, 105, 105, 150));
	mFill.setFillColor(sf::Color::White);
	mHoverFill.setFillColor(sf::Color::Transparent);

	std::string fileName = "chess-pieces.png";
	if (!mTexture.loadFromFile("assets/chess-pieces.png")) std::cout << "Can't open " + fileName << std::endl;
	mTexture.setSmooth(true);
	mSpriteList.setTexture(mTexture);
	mSpriteList.setScale(sf::Vector2f{ .75f,.75f });
	mSpriteList.setTextureRect({ 1 * 133, (int)mSide * 133, 4*133, 133 });

	mFill.setPosition(sf::Vector2f{ (Board::TILECOUNT * Board::TILESIZE / 2) - sf::Vector2i(2 * Board::TILESIZE, Board::TILESIZE / 2) });
	mSpriteList.setPosition(sf::Vector2f{ (Board::TILECOUNT * Board::TILESIZE / 2) - sf::Vector2i(2 * Board::TILESIZE, Board::TILESIZE / 2) });
}

void PromoteOption::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBg);
	target.draw(mFill);
	target.draw(mHoverFill);
	target.draw(mSpriteList);
}

void PromoteOption::setChosenType(Type type)
{
	mChosenType = type;
}

Type PromoteOption::getChosenType() const
{
	return mChosenType;
}

void PromoteOption::setSide(Side side)
{
	mSide = side;
	mSpriteList.setTextureRect({ 1 * 133, (int)side * 133, 4 * 133, 133 });
}

Side PromoteOption::getSide() const
{
	return mSide;
}

sf::Sprite PromoteOption::getSprite() const
{
	return mSpriteList;
}

bool PromoteOption::isHovering(sf::Vector2i mousePos)
{
	mHoverFill.setFillColor(sf::Color::Transparent);
	if (mFill.getGlobalBounds().contains((sf::Vector2f)mousePos))
	{
		sf::Vector2f piecePos = mSpriteList.getPosition() + sf::Vector2f((float)((int)((mousePos.x - mSpriteList.getPosition().x) / Board::TILESIZE) * Board::TILESIZE), 0.f);
		mHoverFill.setFillColor(sf::Color(220, 220, 220));
		mHoverFill.setPosition(piecePos);
		Type temp = static_cast<Type>(((mHoverFill.getGlobalBounds().left - mSpriteList.getGlobalBounds().left) / Board::TILESIZE) + 1);
		setChosenType(temp);
		return true;
	}
	return false;
}
