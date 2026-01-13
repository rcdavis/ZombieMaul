#pragma once

#include <filesystem>

#include "SFML/Graphics/Font.hpp"

namespace FontManager {
	sf::Font* LoadFont(const std::filesystem::path& filepath);
}
