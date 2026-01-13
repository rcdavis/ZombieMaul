#include "Game.h"

#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "Renderer/TextureManager.h"
#include "Utils/Log.h"

Game::Game() :
	mWindow(),
	mBg()
{}

Game::~Game() {
	Shutdown();
}

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

	sf::Texture* tex = TextureManager::LoadTexture("res/textures/MenuBG1.png");
	if (!tex) {
		LOG_ERROR("Failed to load test texture");
		return false;
	}

	mBg = std::make_unique<sf::Sprite>(*tex);
	mBg->setScale({0.8f, 0.75f});
	mBg->setPosition({0.0f, -20.0f});

	return true;
}

void Game::Shutdown() {
	mBg = nullptr;
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

	mWindow.draw(*mBg);

	mWindow.display();
}
