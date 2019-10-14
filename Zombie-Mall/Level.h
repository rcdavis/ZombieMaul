
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

private:
	Game& mGame;

	sf::Sprite mBGImage;
};

#endif // !_LEVEL_H_
