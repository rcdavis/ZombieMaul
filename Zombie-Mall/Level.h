
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/Graphics/Sprite.hpp>

class Game;

namespace sf
{
	class RenderTarget;
}

class Level
{
public:
	Level(Game& game);
	~Level();

	bool LoadLevel();

	void Render(sf::RenderTarget* renderTarget);

	const float GetWidth() const { return mWidth; }
	const float GetHeight() const { return mHeight; }

private:
	Game& mGame;

	sf::Sprite mBGImage;

	float mWidth;
	float mHeight;
};

#endif // !_LEVEL_H_
