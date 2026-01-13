#include "Game.h"

#include <optional>

#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Image.hpp"

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"
#include "Renderer/FontManager.h"

#include "States/MainMenuState.h"

#include "Input/Input.h"
#include "Utils/Log.h"

static std::optional<sf::Text> testText;

Game::Game() :
	mStateManager(),
	mWindow()
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

		mStateManager.ProcessStateChange();

		const sf::Time elapsedTime = clock.restart();
		lag += elapsedTime;

		if (!Input()) {
			Close();
			break;
		}

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
	mSettings.Load("res/data/Settings.txt");

	mWindow.create(sf::VideoMode({800, 600}), "Zombie Maul");

	sf::Image icon;
	if (icon.loadFromFile("res/textures/zombie-maul-icon.png"))
		mWindow.setIcon(icon);

	mStateManager.PushState(std::make_unique<MainMenuState>(*this));

	sf::Font* font = FontManager::LoadFont("res/fonts/FreeSans.ttf");
	if (font) {
		testText.emplace(*font, "Test Text");
		testText->setPosition({0.0f, 0.0f});
	}

	return true;
}

void Game::Shutdown() {
	mStateManager.ClearStates();

	mSettings.Save("res/data/Settings.txt");
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

bool Game::Input() {
	Input::Poll();
	return mStateManager.Input();
}

void Game::Update() {
	mStateManager.Update();
}

void Game::Render() {
	mWindow.clear(sf::Color::Magenta);

	mStateManager.Render(&mWindow);
	mWindow.draw(*testText);

	mWindow.display();
}
