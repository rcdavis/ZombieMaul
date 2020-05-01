
#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include <LuaBridge/LuaBridge.h>

#include <iostream>

#include "Input/InputManager.h"
#include "States/MainMenuState.h"

Game::Game() :
    mWindow(),
    mTextureManager(),
    mFontManager(),
    mAnimationManager(),
    mEventManager(),
    mEntityManager(),
    mStateManager(),
    mSettings(),
    mLuaState(luaL_newstate()),
    mTimeMultiplier(1.0f),
    mTextEntity(nullptr),
    mTimeStepPerFrame(sf::seconds(1.0f / 60.0f)),
    mScore(0)
{
    luaL_openlibs(mLuaState);
}

Game::~Game()
{
    lua_close(mLuaState);
}

bool Game::Run()
{
    if (Init() == false)
        return false;

    sf::Clock clock;
    sf::Time lag;

    while (mWindow.isOpen())
    {
        PollWindowEvents();

        mStateManager.ProcessStateChange();

        const sf::Time elapsedTime = clock.restart() * mTimeMultiplier;
        lag += elapsedTime;

        if (Input() == false)
        {
            Close();
            break;
        }

        while (lag >= mTimeStepPerFrame)
        {
            Update();

#ifdef DEBUG
            if (lag >= (mTimeStepPerFrame * 2.0f))
                lag = mTimeStepPerFrame;
#endif // DEBUG

            lag -= mTimeStepPerFrame;
        }

        Render(lag / mTimeStepPerFrame);
    }

    Shutdown();

    return true;
}

bool Game::Init()
{
    if (!LoadConfig())
        return false;

    mSettings.Load("Resources/Data/Settings.json");

    mEventManager.RegisterListener("Player Died", this);
    mEventManager.RegisterListener("Player Hit Civilian", this);

    mStateManager.PushState(std::make_unique<MainMenuState>(*this));

    return true;
}

void Game::Shutdown()
{
    mSettings.Save("Resources/Data/Settings.json");

    mStateManager.ClearStates();
}

bool Game::Input()
{
    InputManager::Global.Poll();

    return mStateManager.Input();
}

void Game::Update()
{
    mStateManager.Update();

    mEventManager.ProcessEvents();
}

void Game::Render(float lerpBetweenFrame)
{
    mWindow.clear(sf::Color::Magenta);

    mStateManager.Render(&mWindow);

    mWindow.display();
}

void Game::PollWindowEvents()
{
    sf::Event e;
    while (mWindow.pollEvent(e))
    {
        switch (e.type)
        {
        case sf::Event::Closed:
            Close();
            break;
        }
    }
}

void Game::HandleEvent(const Event* const pEvent)
{
    if (pEvent->GetId() == "Player Died")
    {
        mStateManager.ClearAndSetState(std::make_unique<MainMenuState>(*this));
    }
    else if (pEvent->GetId() == "Player Hit Civilian")
    {
        ++mScore;
    }
}

bool Game::LoadConfig()
{
    luaL_dofile(mLuaState, "Resources/Scripts/Config.lua");

    std::string title = "Default Title";
    unsigned int width = 400U, height = 300U;

    luabridge::LuaRef appRef = luabridge::getGlobal(mLuaState, "app");
    if (!appRef.isTable())
        return false;

    luabridge::LuaRef windowRef = appRef["window"];
    if (!windowRef.isTable())
        return false;

    luabridge::LuaRef titleRef = windowRef["title"];
    if (titleRef.isString())
        title = titleRef.cast<std::string>();

    luabridge::LuaRef sizeRef = windowRef["size"];
    if (sizeRef.isTable())
    {
        if (sizeRef["width"].isNumber())
            width = sizeRef["width"].cast<unsigned int>();

        if (sizeRef["height"].isNumber())
            height = sizeRef["height"].cast<unsigned int>();
    }

    mWindow.create(sf::VideoMode(width, height), title);

    luabridge::LuaRef iconRef = windowRef["icon"];
    if (iconRef.isString())
    {
        sf::Image icon;
        if (icon.loadFromFile(iconRef.cast<std::string>()))
        {
            mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }
    }

    return true;
}

void Game::Close()
{
    mWindow.close();
}