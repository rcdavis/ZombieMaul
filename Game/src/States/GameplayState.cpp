#include "States/GameplayState.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

#include <optional>

#include "States/MainMenuState.h"

#include "Input/Input.h"
#include "Game.h"

#include "Renderer/Animation.h"
#include "Renderer/AnimationManager.h"
#include "Renderer/FontManager.h"
#include "Renderer/TextureManager.h"

GameplayState::GameplayState(Game& game) :
	mLevel(game),
	mPlayer(game),
	mGame(game)
{}

GameplayState::~GameplayState() {

}

void GameplayState::Enter() {
	mLevel.LoadLevel("res/data/Level.json");

	const Animation* playerAnim = AnimationManager::Load("res/data/PlayerWalkAnim.json");
	mPlayer.SetAnimation(playerAnim);

	auto tex = TextureManager::LoadTexture("res/textures/CharacterSprite.png");
	if (tex) {
		mPlayer.SetSprite(sf::Sprite(*tex));
		mPlayer.SetTextureRect(sf::IntRect({0, 0}, {64, 64}));
		mPlayer.SetOrigin({32.0f, 32.0f});
		mPlayer.SetPosition({300.0f, 300.0f});
		mPlayer.SetRotation(sf::degrees(180.0f));
		mPlayer.SetSpeed(5.0f);
	}
}

void GameplayState::Exit() {
    mGame.GetWindow().setView(mGame.GetWindow().getDefaultView());
}

bool GameplayState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Escape))
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));

	if (Input::IsKeyPressed(sf::Keyboard::Key::F1))
		mGame.GetSettings().SetDebugRender(!mGame.GetSettings().GetDebugRender());

	return true;
}

void GameplayState::Update() {
	mPlayer.Update();

	for (const auto& bounds : mLevel.GetCollisionBounds()) {
		mPlayer.HandleCollision(bounds);
	}
}

void GameplayState::Render(sf::RenderTarget* const renderTarget) {
	if (mGame.GetStateManager().GetCurrentState() != this)
		return;

	const sf::Vector2f playerPos(mPlayer.GetPosition());
	const sf::Vector2f windowSize(mGame.GetWindow().getSize());

	const sf::Vector2f center(
		std::clamp(playerPos.x, windowSize.x / 2.0f, mLevel.GetWidth() - (windowSize.x / 2.0f)),
		std::clamp(playerPos.y, windowSize.y / 2.0f, mLevel.GetHeight() - (windowSize.y / 2.0f)));

	const sf::View view(center, windowSize);
	mGame.GetWindow().setView(view);

	mLevel.Render(renderTarget);
	mPlayer.Render(renderTarget);
}
