
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
	mLevel.LoadLevel("Resources/Data/Level.json");

	CreatePlayer();
}

void GameplayState::Exit()
{
	mGame.GetEntityManager().RemoveEntity(mPlayer);
	mPlayer = nullptr;

	mGame.GetWindow().setView(mGame.GetWindow().getDefaultView());
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
	mLevel.HandleCollision(mPlayer);
}

void GameplayState::Render(sf::RenderTarget* renderTarget)
{
	const sf::Vector2f playerPos(mPlayer->GetPosition());
	const sf::Vector2f windowSize(mGame.GetWindow().getSize());

	sf::Vector2f center;
	center.x = std::clamp(playerPos.x, windowSize.x / 2.0f, mLevel.GetWidth() - (windowSize.x / 2.0f));
	center.y = std::clamp(playerPos.y, windowSize.y / 2.0f, mLevel.GetHeight() - (windowSize.y / 2.0f));

	const sf::View view(center, windowSize);
	mGame.GetWindow().setView(view);

	mLevel.Render(renderTarget);
}

void GameplayState::CreatePlayer()
{
	std::unique_ptr<Player> player = std::make_unique<Player>();

	player->SetPosition(sf::Vector2f(300.0f, 300.0f));
	player->SetRotation(180.0f);
	player->SetSpeed(5.0f);

	player->SetTextureRect(sf::IntRect(0, 0, 64, 64));
	player->SetOrigin(sf::Vector2f(32.0f, 32.0f));

	auto texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/CharacterSprite.png");
	if (texture)
	{
		player->SetTexture(texture);
	}

	auto anim = mGame.GetAnimationManager().LoadAnimation("Resources/Data/Player.json");
	if (anim)
	{
		player->SetAnimation(anim);
	}

	mPlayer = player.get();
	mGame.GetEntityManager().AddEntity(std::move(player));
}