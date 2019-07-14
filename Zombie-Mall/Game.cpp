
#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <LuaBridge/LuaBridge.h>

#include <iostream>

Game::Game() :
	mWindow(),
	mTextureManager(),
	mEventManager(),
	mSettings(),
	mLuaState(luaL_newstate())
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

		sf::Time elapsedTime = clock.restart();
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

	return true;
}

void Game::Shutdown()
{
	mSettings.Save("Resources/Data/Settings.json");
}

void Game::Update()
{
	mEventManager.ProcessEvents();
}

void Game::Render(float lerpBetweenFrame)
{
	mWindow.clear(sf::Color::Magenta);



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
		auto icon = sf::Image();
		if (icon.loadFromFile(iconRef.cast<std::string>()))
		{
			mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		}
	}

	return true;
}