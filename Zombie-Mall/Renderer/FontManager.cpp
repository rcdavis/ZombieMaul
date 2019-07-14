
#include "FontManager.h"

FontManager::FontManager() {}
FontManager::~FontManager() {}

sf::Font* FontManager::LoadFont(std::filesystem::path file)
{
	sf::Font* result = nullptr;

	auto iter = mFonts.find(file);
	if (iter == std::end(mFonts))
	{
		std::unique_ptr<sf::Font> loadedFont = std::make_unique<sf::Font>();
		if (loadedFont->loadFromFile(file.string()))
		{
			result = loadedFont.get();
			mFonts[file] = std::move(loadedFont);
		}

	}
	else
	{
		result = iter->second.get();
	}

	return result;
}