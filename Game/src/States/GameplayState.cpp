#include "States/GameplayState.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

#include <optional>

#include "States/MainMenuState.h"
#include "States/PauseMenuState.h"

#include "Entity/EntityManager.h"
#include "Entity/Player.h"
#include "Entity/Person.h"
#include "Entity/Guard.h"

#include "Input/Input.h"
#include "Game.h"
#include "Identifier.h"

#include "Renderer/Animation.h"
#include "Renderer/AnimationManager.h"
#include "Renderer/FontManager.h"
#include "Renderer/TextureManager.h"

GameplayState::GameplayState(Game& game) :
	mLevel(game),
	mSpawns(),
	mScoreText(),
	mPlayer(nullptr),
	mGame(game)
{}

GameplayState::~GameplayState() {

}

void GameplayState::Enter() {
	mLevel.LoadLevel(Id::Data::Level);

	SpawnPlayer();

	mSpawns.emplace_back(mLevel.GetPersonSpawnTime(), std::bind(&GameplayState::SpawnPerson, this));
	mSpawns.emplace_back(mLevel.GetGuardSpawnTime(), std::bind(&GameplayState::SpawnGuard, this));

	mGame.SetScore(0);
	auto font = FontManager::LoadFont(Id::Fonts::FreeSans);
	if (font) {
		mScoreText.emplace(*font);
		mScoreText->setString("Score: 0");
	}
}

void GameplayState::Exit() {
	mScoreText.reset();
	mSpawns.clear();
	mGame.GetWindow().setView(mGame.GetWindow().getDefaultView());
	EntityManager::ClearEntities();
}

bool GameplayState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Escape))
		mGame.GetStateManager().PushState(std::make_unique<PauseMenuState>(mGame));

	if (Input::IsKeyPressed(sf::Keyboard::Key::F1))
		mGame.GetSettings().SetDebugRender(!mGame.GetSettings().GetDebugRender());

	return true;
}

void GameplayState::Update() {
	if (mGame.GetStateManager().GetCurrentState() != this) {
		for (auto& spawn : mSpawns)
			spawn.ResetTimer();
		return;
	}

	mLevel.HandleCollisions();

	for (auto& spawn : mSpawns)
		spawn.Update();

	EntityManager::Update();

	char buffer[16] = {};
	snprintf(buffer, sizeof(buffer), "Score: %d", mGame.GetScore());
	mScoreText->setString(buffer);
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

	mScoreText->setPosition(center - (windowSize / 2.0f));
	mScoreText->move({5.0f, 2.0f});
	renderTarget->draw(*mScoreText);
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

void GameplayState::SpawnGuard() {
	std::unique_ptr<Guard> guard = std::make_unique<Guard>(mGame, mPlayer);
	guard->Load("res/data/Guard.json");

	if (mPlayer->GetPosition().x > (mLevel.GetWidth() / 2.0f))
		guard->SetPosition({300.0f, 100.0f});
	else
		guard->SetPosition({1300.0f, 100.0f});

	EntityManager::AddEntity(std::move(guard));
}
