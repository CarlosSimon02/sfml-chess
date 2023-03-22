#include "GameState.hpp"

GameState::GameState()
{}

void GameState::display(sf::RenderWindow& window)
{
	for (auto& drawable : mDrawables) 
		window.draw(*drawable);
	if (mPiecesBuffer.getPromotingStat()) 
		window.draw(mPromoteOp);
}

void GameState::handleEvents(sf::RenderWindow& window, sf::Event& event)
{
	setGameOverStat();

	while (window.waitEvent(event))
	{
		if (event.type == sf::Event::Closed) 
			window.close();

		if (getGameOverStat() && 
			(event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::MouseButtonPressed))
		{
			PiecesBuffer init;
			mPiecesBuffer = std::move(init);
			mIsGameOver = false;
			return;
		}

		if (mPiecesBuffer.getPromotingStat())
		{
			if (mPromoteOp.isHovering(sf::Mouse::getPosition(window)) &&
				event.type == sf::Event::MouseButtonPressed)
			{
				mPiecesBuffer.setPromotingStat(false);
				mPiecesBuffer.promote(mPiecesBuffer.getLastMovedPiecePos(), mPromoteOp.getChosenType());
			}
			return;
		}

		if (event.type == sf::Event::MouseButtonPressed &&
			!mPiecesBuffer.getPromotingStat() &&
			!getGameOverStat())
		{
			if (mOldMousePos >= 0)
			{
				int newMousePos = Board::getBufPos({ sf::Mouse::getPosition(window) / (int)Board::TILESIZE });
				if (mHighlights.isInPositionChoices(Board::getVecPos(newMousePos)) && newMousePos != mOldMousePos)
				{
					mPiecesBuffer.movePiece(mOldMousePos, newMousePos);
					if (mPiecesBuffer.getPromotingStat()) mPromoteOp.setSide(mPiecesBuffer.getPlygSide());
					mPiecesBuffer.setPlygSide((mPiecesBuffer.getPlygSide() == Side::Black) ? Side::White : Side::Black);
				}
				mHighlights.clear();
				mOldMousePos = -1;
				return;
			}
			if (mPiecesBuffer.hasPiece({ sf::Mouse::getPosition(window) / (int)Board::TILESIZE }, mPiecesBuffer.getPlygSide()))
			{
				mOldMousePos = Board::getBufPos({ sf::Mouse::getPosition(window) / (int)Board::TILESIZE });
				mHighlights.setPositions(mPiecesBuffer[mOldMousePos]->validPosList(mPiecesBuffer));
				return;
			}
		}
	}
}

void GameState::setGameOverStat()
{
	mPiecesBuffer.setStaleMateStat();
	mPiecesBuffer.setCheckMateStat();

	if (mPiecesBuffer.getCheckMateStat() ||
		mPiecesBuffer.getStaleMateStat())
	{
		std::cout << "Game over, press any key to restart..." << std::endl;
		mIsGameOver = true;
		return;
	}

	mIsGameOver = false;
	return;
}

bool GameState::getGameOverStat()
{
	return mIsGameOver;
}
