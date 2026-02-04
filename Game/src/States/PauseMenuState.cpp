#include "States/PauseMenuState.h"

#include "Game.h"
#include "Input/Input.h"
#include "Renderer/TextureManager.h"
#include "Renderer/FontManager.h"
#include "States/OptionsMenuState.h"
#include "States/MainMenuState.h"

#include "SFML/Graphics/Font.hpp"

PauseMenuState::PauseMenuState(Game& game) :
	mBgImage(),
	mIcon(),
	mEntries(),
	mCurEntry(0),
	mGame(game)
{}

PauseMenuState::~PauseMenuState() {

}

void PauseMenuState::Enter() {
	mCurEntry = 0;

	auto texture = TextureManager::LoadTexture("res/textures/MenuBG1.png");
	if (texture) {
		mBgImage.emplace(*texture);
		mBgImage->setScale({0.8f, 0.75f});
		mBgImage->setPosition({0.0f, -20.0f});
	}

	texture = TextureManager::LoadTexture("res/textures/MenuPointer.png");
	if (texture) {
		mIcon.emplace(*texture);
		mIcon->setScale({0.5f, 0.5f});
	}

	auto font = FontManager::LoadFont("res/fonts/FreeSans.ttf");
	if (font) {
		AddTextEntry(font, "Continue", {300.0f, 400.0f});
		AddTextEntry(font, "Options", {300.0f, 450.0f});
		AddTextEntry(font, "Exit", {300.0f, 500.0f});
	}
}

void PauseMenuState::Exit() {
	mBgImage.reset();
	mIcon.reset();
	mEntries.clear();
}

bool PauseMenuState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Up)) {
		if (mCurEntry > 0)
			--mCurEntry;
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Down)) {
		if (mCurEntry < std::size(mEntries) - 1)
			++mCurEntry;
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Enter))
		return ProcessEnter();

	return true;
}

void PauseMenuState::Update() {
	mIcon->setPosition({150.0f, 350.0f + (mCurEntry * 50.0f)});
}

void PauseMenuState::Render(sf::RenderTarget* const renderTarget) {
	const sf::Vector2f windowSize(mGame.GetWindow().getSize());
	const sf::FloatRect bounds({0.0f, 0.0f}, {windowSize.x, windowSize.y});

	mGame.GetWindow().setView(sf::View(bounds));

	renderTarget->draw(*mBgImage);

	if (mGame.GetStateManager().GetCurrentState() == this) {
		for (auto& entry : mEntries)
			renderTarget->draw(entry);

		renderTarget->draw(*mIcon);
	}
}

bool PauseMenuState::ProcessEnter() {
	switch (mCurEntry) {
	case MenuItems::eContinue:
		mGame.GetStateManager().PopState();
		break;

	case MenuItems::eOptions:
		mGame.GetStateManager().PushState(std::make_unique<OptionsMenuState>(mGame));
		break;

	case MenuItems::eExit:
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));
		break;
	}

	return true;
}

void PauseMenuState::AddTextEntry(sf::Font* font, const char* const text, const sf::Vector2f pos) {
	mEntries.emplace_back(*font, text);
	mEntries.back().setPosition(pos);
}
