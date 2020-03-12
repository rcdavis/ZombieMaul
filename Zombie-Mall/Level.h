
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/Graphics/Sprite.hpp>

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

	void HandleCollision(Entity* const entity) const;

	void Render(sf::RenderTarget* const renderTarget);

	const float GetWidth() const { return mWidth; }
	const float GetHeight() const { return mHeight; }

private:
	std::vector<Capsule> mCollisionBounds;

	Game& mGame;

	sf::Sprite mBGImage;

	float mWidth;
	float mHeight;
};

#endif // !_LEVEL_H_
