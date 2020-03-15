
#include "GameplayState.h"

#include "../Game.h"
#include "../Input/InputManager.h"
#include "MainMenuState.h"
#include "../Entity/Player.h"
#include "../Entity/Person.h"

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
	CreatePerson();

	mSpawnTimer.restart();
}

void GameplayState::Exit()
{
	mGame.GetEntityManager().ClearEntities();
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
	mLevel.HandleCollisions();

	if (mSpawnTimer.getElapsedTime() > mLevel.GetSpawnTime())
	{
		CreatePerson();
		mSpawnTimer.restart();
	}
}

void GameplayState::Render(sf::RenderTarget* const renderTarget)
{
	const sf::Vector2f playerPos(mPlayer->GetPosition());
	const sf::Vector2f windowSize(mGame.GetWindow().getSize());

	const sf::Vector2f center(
		std::clamp(playerPos.x, windowSize.x / 2.0f, mLevel.GetWidth() - (windowSize.x / 2.0f)),
		std::clamp(playerPos.y, windowSize.y / 2.0f, mLevel.GetHeight() - (windowSize.y / 2.0f)));

	const sf::View view(center, windowSize);
	mGame.GetWindow().setView(view);

	mLevel.Render(renderTarget);
}

void GameplayState::CreatePlayer()
{
	std::unique_ptr<Player> player = std::make_unique<Player>(mGame);
	player->Load("Resources/Data/Player.json");

	mPlayer = player.get();
	mGame.GetEntityManager().AddEntity(std::move(player));
}

void GameplayState::CreatePerson()
{
	std::unique_ptr<Person> person = std::make_unique<Person>(mGame);
	person->Load("Resources/Data/Person.json");

	if (mPlayer->GetPosition().x > (mLevel.GetWidth() / 2.0f))
		person->SetPosition(sf::Vector2f(300.0f, 100.0f));
	else
		person->SetPosition(sf::Vector2f(1300.0f, 100.0f));

	mGame.GetEntityManager().AddEntity(std::move(person));
}