#include "Renderer/FontManager.h"

#include <map>
#include <memory>

namespace FontManager {
    static std::map<std::filesystem::path, std::unique_ptr<sf::Font> > loadedFonts;

	sf::Font* LoadFont(const std::filesystem::path& filepath) {
		auto iter = loadedFonts.find(filepath);
		if (iter != std::end(loadedFonts))
			return iter->second.get();

		std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
		if (!font->openFromFile(filepath))
			return nullptr;

		sf::Font* const result = font.get();
		loadedFonts[filepath] = std::move(font);
		return result;
	}
}
