
#include "GameplayState.h"

#include "../Game.h"
#include "../Input/InputManager.h"
#include "MainMenuState.h"

GameplayState::GameplayState(Game& game) :
	mGame(game),
	mLevel(game)
{}

GameplayState::~GameplayState() {}

void GameplayState::Enter()
{
	mLevel.LoadLevel();
}

void GameplayState::Exit()
{

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
	mLevel.Render(renderTarget);
}