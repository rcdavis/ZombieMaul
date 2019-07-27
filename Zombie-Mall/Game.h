
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics/RenderWindow.hpp>

#include <lua.hpp>

#include "Renderer/TextureManager.h"
#include "Renderer/FontManager.h"
#include "Messaging/EventManager.h"
#include "Entity/EntityManager.h"
#include "States/StateManager.h"

#include "Settings.h"

#include "Entity/TextEntity.h"

class Game
{
public:
	Game();
	~Game();

	bool Run();

	TextureManager& GetTextureManager() { return mTextureManager; }
	FontManager& GetFontManager() { return mFontManager; }
	EntityManager& GetEntityManager() { return mEntityManager; }
	StateManager& GetStateManager() { return mStateManager; }

	Settings& GetSettings() { return mSettings; }

private:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool Init();
	void Shutdown();

	bool Input();
	void Update();
	void Render(float lerpBetweenFrame);

	void PollWindowEvents();

	bool LoadConfig();

	void Close();

	sf::RenderWindow mWindow;

	TextureManager mTextureManager;
	FontManager mFontManager;
	EventManager mEventManager;
	EntityManager mEntityManager;
	StateManager mStateManager;

	Settings mSettings;

	lua_State* mLuaState;

	float mTimeMultiplier;

	TextEntity* mTextEntity;
};

#endif // !_GAME_H_
