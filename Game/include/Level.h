#pragma once

#include <optional>
#include <filesystem>

#include "SFML/Graphics/Sprite.hpp"

namespace sf {
	class RenderTarget;
}

class Game;

class Level {
public:
	Level(Game& game);
	~Level();

	void Render(sf::RenderTarget* const renderTarget);

	bool LoadLevel(const std::filesystem::path& file);

private:
	std::optional<sf::Sprite> mBgSprite;

	Game& mGame;

	float mWidth;
	float mHeight;
};
