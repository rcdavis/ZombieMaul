#include "States/OptionsMenuState.h"

#include "Game.h"
#include "Identifier.h"
#include "Input/Input.h"
#include "Renderer/FontManager.h"
#include "Renderer/TextureManager.h"

#include "SFML/Graphics/RenderTarget.hpp"

OptionsMenuState::OptionsMenuState(Game& game) :
	mEntries(),
	mIconSprite(),
	mCurEntry(0),
	mGame(game)
{}

OptionsMenuState::~OptionsMenuState() {

}

void OptionsMenuState::Enter() {
	mCurEntry = 0;

	auto font = FontManager::LoadFont(Id::Fonts::FreeSans);
	if (font) {
		char buffer[32] = {};

		snprintf(buffer, sizeof(buffer), "Music Volume < %d >", mGame.GetSettings().GetMusicVolume());
		mEntries.emplace_back(*font, buffer);
		mEntries.back().setPosition({300.0f, 400.0f});

		snprintf(buffer, sizeof(buffer), "Sfx Volume < %d >", mGame.GetSettings().GetSfxVolume());
		mEntries.emplace_back(*font, buffer);
		mEntries.back().setPosition({300.0f, 450.0f});

		mEntries.emplace_back(*font, "Exit");
		mEntries.back().setPosition({300.0f, 500.0f});
	}

	auto tex = TextureManager::LoadTexture("res/textures/MenuPointer.png");
	if (tex) {
		mIconSprite.emplace(*tex);
		mIconSprite->setScale({0.5f, 0.5f});
		mIconSprite->setPosition({150.0f, 350.0f});
	}
}

void OptionsMenuState::Exit() {
	mEntries.clear();
	mIconSprite.reset();
}

bool OptionsMenuState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Up)) {
		if (mCurEntry > 0)
			--mCurEntry;
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Down)) {
		if (mCurEntry < MenuItems::eNum - 1)
			++mCurEntry;
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Left)) {
		DecreaseMenuItemValue();
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Right)) {
		IncreaseMenuItemValue();
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Enter)) {
		return ProcessEnter();
	}

	return true;
}

void OptionsMenuState::Update() {
	mIconSprite->setPosition({150.0f, 350.0f + (mCurEntry * 50.0f)});

	char buffer[32] = {};

	snprintf(buffer, sizeof(buffer), "Music Volume < %d >", mGame.GetSettings().GetMusicVolume());
	mEntries[MenuItems::eMusicVolume].setString(buffer);

	snprintf(buffer, sizeof(buffer), "Sfx Volume < %d >", mGame.GetSettings().GetSfxVolume());
	mEntries[MenuItems::eSfxVolume].setString(buffer);
}

void OptionsMenuState::Render(sf::RenderTarget* const renderTarget) {
	for (auto& entry : mEntries)
		renderTarget->draw(entry);

	renderTarget->draw(*mIconSprite);
}

bool OptionsMenuState::ProcessEnter() {
	if (mCurEntry == MenuItems::eExit)
		mGame.GetStateManager().PopState();

	return true;
}

void OptionsMenuState::DecreaseMenuItemValue() {
	switch (mCurEntry) {
	case MenuItems::eMusicVolume:
		{
			auto& settings = mGame.GetSettings();
			settings.SetMusicVolume(settings.GetMusicVolume() - 1);
		}
		break;

	case MenuItems::eSfxVolume:
		{
			auto& settings = mGame.GetSettings();
			settings.SetSfxVolume(settings.GetSfxVolume() - 1);
		}
		break;
	}
}

void OptionsMenuState::IncreaseMenuItemValue() {
	switch (mCurEntry) {
	case MenuItems::eMusicVolume:
		{
			auto& settings = mGame.GetSettings();
			settings.SetMusicVolume(settings.GetMusicVolume() + 1);
		}
		break;

	case MenuItems::eSfxVolume:
		{
			auto& settings = mGame.GetSettings();
			settings.SetSfxVolume(settings.GetSfxVolume() + 1);
		}
		break;
	}
}
