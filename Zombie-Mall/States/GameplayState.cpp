
#include "GameplayState.h"

#include <iostream>

#include "../Game.h"
#include "../Input/InputManager.h"
#include "MainMenuState.h"

GameplayState::GameplayState(Game& game) :
	mGame(game)
{}

GameplayState::~GameplayState() {}

void GameplayState::Enter()
{
	std::cout << "Entering Gameplay State" << std::endl;
}

void GameplayState::Exit()
{
	std::cout << "Exiting Gameplay State" << std::endl;
}

bool GameplayState::Input()
{
	if (InputManager::Global.IsKeyPressed(sf::Keyboard::Escape))
	{
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));
	}

	return true;
}

void GameplayState::Update()
{

}

void GameplayState::Render(sf::RenderTarget* renderTarget)
{

}