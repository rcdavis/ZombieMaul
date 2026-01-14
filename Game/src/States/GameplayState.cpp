#include "States/GameplayState.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

#include <optional>

#include "States/MainMenuState.h"

#include "Input/Input.h"
#include "Game.h"

#include "Renderer/FontManager.h"

static std::optional<sf::Text> testText;

GameplayState::GameplayState(Game& game) :
	mGame(game)
{}

GameplayState::~GameplayState() {

}

void GameplayState::Enter() {
	auto font = FontManager::LoadFont("res/fonts/FreeSans.ttf");
	if (font)
		testText.emplace(*font, "Gameplay State");
}

void GameplayState::Exit() {
	testText.reset();
}

bool GameplayState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Escape))
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));

	return true;
}

void GameplayState::Update() {

}

void GameplayState::Render(sf::RenderTarget* const renderTarget) {
	renderTarget->draw(*testText);
}
