#pragma once

#include "SFML/Graphics/Font.hpp"
#include "Identifier.h"

namespace FontManager {
	sf::Font* LoadFont(const Identifier& id);
}
