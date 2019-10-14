
#include "GameplayState.h"

#include "../Game.h"
#include "../Input/InputManager.h"
#include "MainMenuState.h"
#include "../Entity/Player.h"

GameplayState::GameplayState(Game& game) :
	mGame(game),
	mLevel(game),
	mPlayer(nullptr)
{}

GameplayState::~GameplayState() {}

void GameplayState::Enter()
{
	mLevel.LoadLevel();

	CreatePlayer();
}

void GameplayState::Exit()
{
	mGame.GetEntityManager().RemoveEntity(mPlayer);
	mPlayer = nullptr;
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

void GameplayState::CreatePlayer()
{
	std::unique_ptr<Player> player = std::make_unique<Player>();

	player->SetPosition(sf::Vector2f(300.0f, 300.0f));

	player->SetTextureRect(sf::IntRect(0, 0, 64, 64));

	auto texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/CharacterSprite.png");
	if (texture)
	{
		player->SetTexture(texture);
	}

	mPlayer = player.get();
	mGame.GetEntityManager().AddEntity(std::move(player));
}