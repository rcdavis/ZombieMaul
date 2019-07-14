
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <lua.hpp>

#include "Renderer/TextureManager.h"
#include "Renderer/FontManager.h"
#include "Messaging/EventManager.h"
#include "Input/InputManager.h"

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
	FontManager mFontManager;
	EventManager mEventManager;
	InputManager mInputManager;

	Settings mSettings;

	sf::Text mText;

	lua_State* mLuaState;

	float mTimeMultiplier;
};

#endif // !_GAME_H_
