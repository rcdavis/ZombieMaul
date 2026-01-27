#include "States/GameplayState.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

#include <optional>

#include "States/MainMenuState.h"

#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/Person.h"

#include "Input/Input.h"
#include "Game.h"

#include "Renderer/Animation.h"
#include "Renderer/AnimationManager.h"
#include "Renderer/FontManager.h"
#include "Renderer/TextureManager.h"

GameplayState::GameplayState(Game& game) :
	mLevel(game),
	mSpawns(),
	mPlayer(nullptr),
	mGame(game)
{}

GameplayState::~GameplayState() {

}

void GameplayState::Enter() {
	mLevel.LoadLevel("res/data/Level.json");

	SpawnPlayer();

	mSpawns.emplace_back(mLevel.GetPersonSpawnTime(), std::bind(&GameplayState::SpawnPerson, this));
}

void GameplayState::Exit() {
	mSpawns.clear();
	mGame.GetWindow().setView(mGame.GetWindow().getDefaultView());
	EntityManager::ClearEntities();
}

bool GameplayState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Escape))
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));

	if (Input::IsKeyPressed(sf::Keyboard::Key::F1))
		mGame.GetSettings().SetDebugRender(!mGame.GetSettings().GetDebugRender());

	return true;
}

void GameplayState::Update() {
	mLevel.HandleCollisions();

	for (auto& spawn : mSpawns)
		spawn.Update();

	EntityManager::Update();
}

void GameplayState::Render(sf::RenderTarget* const renderTarget) {
	if (mGame.GetStateManager().GetCurrentState() != this)
		return;

	const sf::Vector2f playerPos(mPlayer->GetPosition());
	const sf::Vector2f windowSize(mGame.GetWindow().getSize());

	const sf::Vector2f center(
		std::clamp(playerPos.x, windowSize.x / 2.0f, mLevel.GetWidth() - (windowSize.x / 2.0f)),
		std::clamp(playerPos.y, windowSize.y / 2.0f, mLevel.GetHeight() - (windowSize.y / 2.0f)));

	const sf::View view(center, windowSize);
	mGame.GetWindow().setView(view);

	mLevel.Render(renderTarget);

	EntityManager::Render(renderTarget);
}

void GameplayState::SpawnPlayer() {
	auto player = std::make_unique<Player>(mGame);
	player->Load("res/data/Player.json");
	mPlayer = player.get();
	EntityManager::AddEntity(std::move(player));
}

void GameplayState::SpawnPerson() {
	auto person = std::make_unique<Person>(mGame);
	person->Load("res/data/Person.json");

	if (mPlayer->GetPosition().x > (mLevel.GetWidth() / 2.0f))
		person->SetPosition({300.0f, 100.0f});
	else
		person->SetPosition({1300.0f, 100.0f});

	EntityManager::AddEntity(std::move(person));
}
