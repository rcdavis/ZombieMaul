#pragma once

#include <memory>

#include "SFML/Graphics/RenderWindow.hpp"

#include "States/StateManager.h"

class Game {
public:
	Game();
	~Game();

	bool Run();

	StateManager& GetStateManager() { return mStateManager; }

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

	sf::RenderWindow mWindow;
};
