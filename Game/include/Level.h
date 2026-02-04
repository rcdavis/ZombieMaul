#pragma once

#include <optional>
#include <filesystem>
#include <vector>

#include "SFML/System/Time.hpp"
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

	const sf::Time& GetPersonSpawnTime() const { return mPersonSpawnTime; }
	const sf::Time& GetGuardSpawnTime() const { return mGuardSpawnTime; }

	void HandleCollisions() const;

	void Render(sf::RenderTarget* const renderTarget);

	bool LoadLevel(const std::filesystem::path& file);

private:
	std::vector<Capsule> mCollisionBounds;
	std::optional<sf::Sprite> mBgSprite;

	sf::Time mPersonSpawnTime;
	sf::Time mGuardSpawnTime;

	Game& mGame;

	float mWidth;
	float mHeight;
};
