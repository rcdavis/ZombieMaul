#pragma once

#include <optional>
#include <filesystem>
#include <vector>

#include "SFML/Graphics/Sprite.hpp"

#include "Utils/Math.h"

namespace sf {
	class RenderTarget;
}

class Game;

class Level {
public:
	Level(Game& game);
	~Level();

	float GetWidth() const { return mWidth; }
	float GetHeight() const { return mHeight; }

	void HandleCollisions() const;

	void Render(sf::RenderTarget* const renderTarget);

	bool LoadLevel(const std::filesystem::path& file);

private:
	std::vector<Capsule> mCollisionBounds;
	std::optional<sf::Sprite> mBgSprite;

	Game& mGame;

	float mWidth;
	float mHeight;
};
