
#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <LuaBridge/LuaBridge.h>

#include <iostream>

Game::Game() :
	mWindow(),
	mTextureManager(),
	mFontManager(),
	mEventManager(),
	mInputManager(),
	mSettings(),
	mText(),
	mLuaState(luaL_newstate()),
	mTimeMultiplier(1.0f)
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
	const sf::Time timeStepPerFrame(sf::seconds(1.0f / 60.0f));

	while (mWindow.isOpen())
	{
		PollWindowEvents();

		const sf::Time elapsedTime = clock.restart() * mTimeMultiplier;
		lag += elapsedTime;

		while (lag >= timeStepPerFrame)
		{
			Update();
			lag -= timeStepPerFrame;
		}

		Render(lag / timeStepPerFrame);
	}

	Shutdown();

	return true;
}

bool Game::Init()
{
	if (!LoadConfig())
		return false;

	mSettings.Load("Resources/Data/Settings.json");

	auto font = mFontManager.LoadFont("Resources/Fonts/FreeSans.ttf");
	if (font != nullptr)
	{
		mText.setFont(*font);
		mText.setString("Test String");
	}

	return true;
}

void Game::Shutdown()
{
	mSettings.Save("Resources/Data/Settings.json");
}

void Game::Update()
{
	mInputManager.Poll();

	if (mInputManager.IsKeyDown(sf::Keyboard::Down))
	{
		mText.move(sf::Vector2f(0.0f, 1.0f));
	}

	if (mInputManager.IsKeyPressed(sf::Keyboard::Right))
	{
		mText.move(sf::Vector2f(2.0f, 0.0f));
	}

	if (mInputManager.IsKeyReleased(sf::Keyboard::Up))
	{
		mText.move(sf::Vector2f(0.0f, -1.0f));
	}

	mEventManager.ProcessEvents();
}

void Game::Render(float lerpBetweenFrame)
{
	mWindow.clear(sf::Color::Magenta);

	mWindow.draw(mText);

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
			mWindow.close();
			break;
		}
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