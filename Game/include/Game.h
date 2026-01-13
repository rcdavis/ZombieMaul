#pragma once

#include <memory>

#include "SFML/Graphics/RenderWindow.hpp"

namespace sf {
	class Sprite;
}

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

	std::unique_ptr<sf::Sprite> mBg;
};
