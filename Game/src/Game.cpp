#include "Game.h"

#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Image.hpp"

Game::Game() :
	mWindow()
{}

Game::~Game() {}

bool Game::Run() {
	if (!Init())
		return false;

	constexpr sf::Time timeStepPerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time lag;
	sf::Clock clock;

	while (mWindow.isOpen()) {
		PollWindowEvents();

		const sf::Time elapsedTime = clock.restart();
		lag += elapsedTime;

		while (lag >= timeStepPerFrame) {
			Update();

#ifdef DEBUG
            if (lag >= (timeStepPerFrame * 2.0f))
                lag = timeStepPerFrame;
#endif // DEBUG

            lag -= timeStepPerFrame;
		}

		Render();
	}

	Shutdown();

	return true;
}

bool Game::Init() {
	mWindow.create(sf::VideoMode({800, 600}), "Zombie Maul");

	sf::Image icon;
	if (icon.loadFromFile("res/textures/zombie-maul-icon.png"))
		mWindow.setIcon(icon);

	return true;
}

void Game::Shutdown() {

}

void Game::Close() {
	mWindow.close();
}

void Game::PollWindowEvents() {
	while (const auto e = mWindow.pollEvent()) {
		if (e->is<sf::Event::Closed>())
			Close();
	}
}

void Game::Update() {

}

void Game::Render() {
	mWindow.clear(sf::Color::Magenta);

	mWindow.display();
}
