#pragma once

#include "SFML/Graphics/Font.hpp"

class Identifier;

namespace FontManager {
	sf::Font* LoadFont(const Identifier& id);
}
