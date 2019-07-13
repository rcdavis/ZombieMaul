
#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

Game::Game()
{}

Game::~Game()
{}

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
	mWindow.create(sf::VideoMode(800, 600), "Zombie Mall");

	return true;
}

void Game::Shutdown()
{

}

void Game::Update()
{

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