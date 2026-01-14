#include "States/GameplayState.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

#include <optional>

#include "States/MainMenuState.h"

#include "Input/Input.h"
#include "Game.h"

#include "Renderer/FontManager.h"

GameplayState::GameplayState(Game& game) :
	mLevel(game),
	mGame(game)
{}

GameplayState::~GameplayState() {

}

void GameplayState::Enter() {
	mLevel.LoadLevel("res/data/Level.json");
}

void GameplayState::Exit() {

}

bool GameplayState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Escape))
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));

	return true;
}

void GameplayState::Update() {

}

void GameplayState::Render(sf::RenderTarget* const renderTarget) {
	mLevel.Render(renderTarget);
}
