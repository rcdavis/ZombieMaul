
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

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

    void ResetScore() { mScore = 0; }
    constexpr unsigned int GetScore() const { return mScore; }

private:
    void ClearAndSetState(std::unique_ptr<IState> state) { mStateManager.ClearAndSetState(std::move(state)); }
    void PushState(std::unique_ptr<IState> state) { mStateManager.PushState(std::move(state)); }

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

    // Menu States for Lua
    void PushMenuState(const char* const file);
    void PopState();
    void ClearAndSetMenuState(const char* const file);

    static void BindLua();

private:
    sf::RenderWindow mWindow;

    TextureManager mTextureManager;
    FontManager mFontManager;
    AnimationManager mAnimationManager;
    EventManager mEventManager;
    EntityManager mEntityManager;
    StateManager mStateManager;

    Settings mSettings;

    float mTimeMultiplier;

    const sf::Time mTimeStepPerFrame;

    unsigned int mScore;
};

#endif // !_GAME_H_
