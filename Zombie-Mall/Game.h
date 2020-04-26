
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include <lua.hpp>

#include "Renderer/TextureManager.h"
#include "Renderer/FontManager.h"
#include "Renderer/AnimationManager.h"
#include "Messaging/EventManager.h"
#include "Entity/EntityManager.h"
#include "States/StateManager.h"

#include "Settings.h"

#include "Entity/TextEntity.h"
#include "Messaging/IEventListener.h"

class Game : public IEventListener
{
public:
    Game();
    ~Game();

    bool Run();

    void HandleEvent(const Event* const pEvent) override;

    TextureManager& GetTextureManager() { return mTextureManager; }
    FontManager& GetFontManager() { return mFontManager; }
    AnimationManager& GetAnimationManager() { return mAnimationManager; }
    EntityManager& GetEntityManager() { return mEntityManager; }
    EventManager& GetEventManager() { return mEventManager; }
    StateManager& GetStateManager() { return mStateManager; }

    Settings& GetSettings() { return mSettings; }

    sf::RenderWindow& GetWindow() { return mWindow; }

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
    AnimationManager mAnimationManager;
    EventManager mEventManager;
    EntityManager mEntityManager;
    StateManager mStateManager;

    Settings mSettings;

    lua_State* mLuaState;

    float mTimeMultiplier;

    TextEntity* mTextEntity;

    const sf::Time mTimeStepPerFrame;
};

#endif // !_GAME_H_
