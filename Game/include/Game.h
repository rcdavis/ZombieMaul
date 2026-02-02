#pragma once

#include <memory>

#include "SFML/Graphics/RenderWindow.hpp"

#include "Messaging/IEventListener.h"
#include "States/StateManager.h"
#include "Settings.h"

class Game : public IEventListener {
public:
	Game();
	~Game();

	bool Run();

	void HandleEvent(const Event* const event) override;

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
	uint32_t mScore;
};
