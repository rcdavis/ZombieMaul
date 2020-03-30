
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <filesystem>

#include "Capsule.h"

class Game;
class Entity;

namespace sf
{
	class RenderTarget;
}

class Level
{
public:
	Level(Game& game);
	~Level();

	bool LoadLevel(const std::filesystem::path& file);

	void HandleCollisions() const;

	void Render(sf::RenderTarget* const renderTarget);

	constexpr float GetWidth() const { return mWidth; }
	constexpr float GetHeight() const { return mHeight; }

	const sf::Time GetPersonSpawnTime() const { return mPersonSpawnTime; }
	const sf::Time GetGuardSpawnTime() const { return mGuardSpawnTime; }

private:
	std::vector<Capsule> mCollisionBounds;

	Game& mGame;

	sf::Sprite mBGImage;

	sf::Time mPersonSpawnTime;
	sf::Time mGuardSpawnTime;

	float mWidth;
	float mHeight;
};

#endif // !_LEVEL_H_
