
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics/RenderWindow.hpp>

#include "Renderer/TextureManager.h"

class Game
{
public:
	Game();
	~Game();

	bool Run();

private:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool Init();
	void Shutdown();

	void Update();
	void Render(float lerpBetweenFrame);

	void PollWindowEvents();

	sf::RenderWindow mWindow;

	TextureManager mTextureManager;
};

#endif // !_GAME_H_
