
#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include <iostream>

#include "Lua/LuaUtils.h"

#include "Input/InputManager.h"
#include "States/MainMenuState.h"
#include "States/GameOverState.h"

#include "States/MenuState.h"

Game::Game() :
    mWindow(),
    mTextureManager(),
    mFontManager(),
    mAnimationManager(),
    mEventManager(),
    mEntityManager(),
    mStateManager(),
    mSettings(),
    mTimeMultiplier(1.0f),
    mTimeStepPerFrame(sf::seconds(1.0f / 60.0f)),
    mScore(0)
{}

Game::~Game() {}

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

    LuaUtils::GetGlobalNamespace()
        .addFunction("cout", &Game::Print)
        .beginClass<Game>("Game")
            //.addFunction("pushState", &Game::PushState)
            .addFunction("popState", &Game::PopState)
            .addFunction("pushMenuState", &Game::PushMenuState)
        .endClass();

    MenuState::BindLua();

    LuaUtils::SetGlobal("game", this);

    /*for (const auto& file : std::filesystem::directory_iterator("Resources/Menus"))
    {
        const auto filepath = file.path().string();
        if (!LuaUtils::DoFile(filepath.c_str()))
            std::cout << "Failed to load " << filepath << std::endl;
    }*/

    mSettings.Load("Resources/Data/Settings.json");

    mEventManager.RegisterListener("Player Died", this);
    mEventManager.RegisterListener("Player Hit Civilian", this);

    PushMenuState("Resources/Menus/MainMenu.lua");

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
        mStateManager.ClearAndSetState(std::make_unique<GameOverState>(*this));
    }
    else if (pEvent->GetId() == "Player Hit Civilian")
    {
        ++mScore;
    }
}

bool Game::LoadConfig()
{
    if (!LuaUtils::DoFile("Resources/Scripts/Config.lua"))
        return false;

    std::string title = "Default Title";
    unsigned int width = 400U, height = 300U;

    luabridge::LuaRef appRef = LuaUtils::GetGlobal("app");
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

    // TODO: Fix issues with resizing
    constexpr sf::Uint32 styleFlags = sf::Style::Titlebar | sf::Style::Close;
    mWindow.create(sf::VideoMode(width, height), title, styleFlags);

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

void Game::Print(const char* s)
{
    std::cout << s << std::endl;
}

void Game::PushMenuState(const char* const file)
{
    mStateManager.PushState(std::make_unique<MenuState>(*this, file));
}

void Game::PopState()
{
    mStateManager.PopState();
}

void Game::ClearAndSetMenuState(const char* const file)
{
    mStateManager.ClearAndSetState(std::make_unique<MenuState>(*this, file));
}
