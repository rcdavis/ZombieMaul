
#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include <map>
#include <filesystem>
#include <memory>

#include <SFML/Graphics/Font.hpp>

class FontManager
{
public:
	FontManager();
	~FontManager();

	sf::Font* LoadFont(std::filesystem::path file);

private:
	FontManager(const FontManager&) = delete;
	FontManager& operator=(const FontManager&) = delete;

	std::map<std::filesystem::path, std::unique_ptr<sf::Font> > mFonts;
};

#endif // !_FONT_MANAGER_H_
