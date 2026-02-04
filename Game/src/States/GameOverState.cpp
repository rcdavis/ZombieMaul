#include "States/GameOverState.h"

#include "Game.h"
#include "Identifier.h"
#include "Input/Input.h"
#include "States/MainMenuState.h"
#include "Renderer/FontManager.h"
#include "Renderer/TextureManager.h"

GameOverState::GameOverState(Game& game) :
	mEntries(),
	mBgImage(),
	mGame(game)
{}

GameOverState::~GameOverState() {

}

void GameOverState::Enter() {
	auto font = FontManager::LoadFont(Id::Fonts::FreeSans);
	if (font) {
		AddTextEntry("Game Over", font, {300.0f, 400.0f});

		char buffer[16] = {};
		snprintf(buffer, sizeof(buffer), "Score: %d", mGame.GetScore());
		AddTextEntry(buffer, font, {300.0f, 500.0f});
	}

	auto texture = TextureManager::LoadTexture("res/textures/MenuBG1.png");
	if (texture) {
		mBgImage.emplace(*texture);
		mBgImage->setScale({0.8f, 0.75f});
		mBgImage->setPosition({0.0f, -20.0f});
	}
}

void GameOverState::Exit() {
	mBgImage.reset();
	mEntries.clear();
}

bool GameOverState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Enter))
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));

	return true;
}

void GameOverState::Update() {

}

void GameOverState::Render(sf::RenderTarget* const renderTarget) {
	renderTarget->draw(*mBgImage);

	for (auto& entry : mEntries)
		renderTarget->draw(entry);
}

void GameOverState::AddTextEntry(const char* const str, sf::Font* font, sf::Vector2f pos) {
	mEntries.emplace_back(*font, str);
	mEntries.back().setPosition(pos);
}
