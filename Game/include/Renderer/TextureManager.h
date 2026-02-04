#pragma once

#include "SFML/Graphics/Texture.hpp"

class Identifier;

namespace TextureManager {
	sf::Texture* LoadTexture(const Identifier& id);
}
