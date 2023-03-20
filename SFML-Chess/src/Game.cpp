#include "Game.hpp"

#include <array>

Game::Game()
	: mWindow(sf::VideoMode(800, 800), "SFML-Chess")
{}

void Game::run()
{
	sf::Event e;

	while (mWindow.isOpen())
	{
		mWindow.clear();
		mGameState.display(mWindow);
		mWindow.display();

		mGameState.handleEvents(mWindow, e);
	}
}