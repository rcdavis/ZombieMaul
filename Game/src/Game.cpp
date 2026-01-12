#include "Game.h"

#include "SFML/Window/Event.hpp"

Game::Game() :
	mWindow()
{}

Game::~Game() {}

bool Game::Run() {
	if (!Init())
		return false;

	while (mWindow.isOpen()) {
		while (const auto e = mWindow.pollEvent()) {
			if (e->is<sf::Event::Closed>())
				Close();
		}

		mWindow.clear(sf::Color::Magenta);

		mWindow.display();
	}

	Shutdown();

	return true;
}

bool Game::Init() {
	mWindow.create(sf::VideoMode({800, 600}), "Zombie Maul");
	return true;
}

void Game::Shutdown() {

}

void Game::Close() {
	mWindow.close();
}
