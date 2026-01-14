#pragma once

#include <memory>

#include "SFML/Graphics/RenderWindow.hpp"

#include "States/StateManager.h"
#include "Settings.h"

class Game {
public:
	Game();
	~Game();

	bool Run();

	StateManager& GetStateManager() { return mStateManager; }
	Settings& GetSettings() { return mSettings; }
	sf::RenderWindow& GetWindow() { return mWindow; }

private:
	bool Init();
	void Shutdown();

	void Close();

	void PollWindowEvents();

	bool Input();
	void Update();
	void Render();

private:
	StateManager mStateManager;
	Settings mSettings;

	sf::RenderWindow mWindow;
};
