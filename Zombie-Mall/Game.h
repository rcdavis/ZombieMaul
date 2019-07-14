
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics/RenderWindow.hpp>

#include <lua.hpp>

#include "Renderer/TextureManager.h"
#include "Messaging/EventManager.h"

#include "Settings.h"

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

	bool LoadConfig();

	sf::RenderWindow mWindow;

	TextureManager mTextureManager;
	EventManager mEventManager;

	Settings mSettings;

	lua_State* mLuaState;
};

#endif // !_GAME_H_
