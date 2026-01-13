#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

class Game {
public:
	Game();
	~Game();

	bool Run();

private:
	bool Init();
	void Shutdown();

	void Close();

	void PollWindowEvents();

	void Update();
	void Render();

private:
	sf::RenderWindow mWindow;
};
