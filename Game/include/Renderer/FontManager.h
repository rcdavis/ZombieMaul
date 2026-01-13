#pragma once

#include <filesystem>

namespace sf {
	class Font;
}

namespace FontManager {
	sf::Font* LoadFont(const std::filesystem::path& filepath);
}
