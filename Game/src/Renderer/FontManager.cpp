#include "Renderer/FontManager.h"

#include <map>
#include <memory>

namespace FontManager {
    static std::map<Identifier, std::unique_ptr<sf::Font> > loadedFonts;

	sf::Font* LoadFont(const Identifier& id) {
		auto iter = loadedFonts.find(id);
		if (iter != std::end(loadedFonts))
			return iter->second.get();

		std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
		if (!font->openFromFile(id.GetIdStr()))
			return nullptr;

		sf::Font* const result = font.get();
		loadedFonts[id] = std::move(font);
		return result;
	}
}
