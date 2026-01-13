#pragma once

#include <filesystem>

namespace sf {
	class Texture;
}

namespace TextureManager {
	sf::Texture* LoadTexture(const std::filesystem::path& filepath);
}
