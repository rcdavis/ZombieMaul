#include "Game.h"

#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Image.hpp"

#include "Messaging/EventManager.h"
#include "States/MainMenuState.h"
#include "States/GameOverState.h"

#include "Input/Input.h"
#include "Utils/Log.h"

Game::Game() :
	mStateManager(),
	mSettings(),
	mWindow(),
	mScore(0)
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

		mStateManager.ProcessStateChange();
	}

	return true;
}

void Game::HandleEvent(const Event* const event) {
	const auto id = event->GetId();
	if (id == "Player Hit Civilian")
		++mScore;
	else if (id == "Player Died")
		mStateManager.ClearAndSetState(std::make_unique<GameOverState>(*this));
}

bool Game::Init() {
	mSettings.Load("res/data/Settings.txt");

	EventManager::RegisterListener("Player Died", this);
	EventManager::RegisterListener("Player Hit Civilian", this);

	mWindow.create(sf::VideoMode({800, 600}), "Zombie Maul");

	sf::Image icon;
	if (icon.loadFromFile("res/textures/zombie-maul-icon.png"))
		mWindow.setIcon(icon);

	mStateManager.PushState(std::make_unique<MainMenuState>(*this));
	mStateManager.ProcessStateChange();

	return true;
}

void Game::Shutdown() {
	mStateManager.ClearStates();
	EventManager::Clear();

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

	EventManager::ProcessEvents();
}

void Game::Render() {
	mWindow.clear(sf::Color::Magenta);

	mStateManager.Render(&mWindow);

	mWindow.display();
}
