#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace Input {
	void Poll();

	bool IsKeyPressed(sf::Keyboard::Key key);
	bool IsKeyDown(sf::Keyboard::Key key);
	bool IsKeyReleased(sf::Keyboard::Key key);
}
