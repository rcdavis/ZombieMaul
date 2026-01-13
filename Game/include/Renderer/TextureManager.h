#pragma once

#include <filesystem>

#include "SFML/Graphics/Texture.hpp"

namespace TextureManager {
	sf::Texture* LoadTexture(const std::filesystem::path& filepath);
}
