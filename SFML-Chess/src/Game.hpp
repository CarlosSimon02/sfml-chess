#pragma once

#include "GameState.hpp"

class Game
{
public:
	Game();
	void run();

private:
	sf::RenderWindow mWindow;

	GameState mGameState;
};