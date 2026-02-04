#include "States/MainMenuState.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Renderer/TextureManager.h"
#include "Input/Input.h"
#include "Game.h"
#include "Identifier.h"

#include "States/CreditsMenuState.h"
#include "States/GameplayState.h"
#include "States/OptionsMenuState.h"

MainMenuState::MainMenuState(Game& game) :
	mEntries(),
	mBgSprite(),
	mIconSprite(),
	mGame(game),
	mCurEntry(0)
{}

MainMenuState::~MainMenuState() {}

void MainMenuState::Enter() {
	mCurEntry = 0;

	sf::Texture* tex = TextureManager::LoadTexture(Id::Textures::MenuBg);
	if (tex) {
		tex->setSmooth(true);
		mBgSprite.emplace(*tex);
		mBgSprite->setScale({0.8f, 0.75f});
		mBgSprite->setPosition({0.0f, -20.0f});
	}

	tex = TextureManager::LoadTexture(Id::Textures::MenuPointer);
	if (tex) {
		tex->setSmooth(true);
		mIconSprite.emplace(*tex);
		mIconSprite->setScale({0.8f, 0.8f});
	}

	mEntries.reserve(MenuItems::eNum);
	tex = TextureManager::LoadTexture(Id::Textures::MenuPlay);
	if (tex) {
		tex->setSmooth(true);
		mEntries.emplace_back(*tex);
	}

	tex = TextureManager::LoadTexture(Id::Textures::MenuOptions);
	if (tex) {
		tex->setSmooth(true);
		mEntries.emplace_back(*tex);
	}

	tex = TextureManager::LoadTexture(Id::Textures::MenuCredits);
	if (tex) {
		tex->setSmooth(true);
		mEntries.emplace_back(*tex);
	}

	tex = TextureManager::LoadTexture(Id::Textures::MenuExit);
	if (tex) {
		tex->setSmooth(true);
		mEntries.emplace_back(*tex);
	}
}

void MainMenuState::Exit() {
	mEntries.clear();
	mBgSprite.reset();
	mIconSprite.reset();
}

bool MainMenuState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Up)) {
		if (mCurEntry > 0)
			--mCurEntry;
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Down)) {
		if (mCurEntry < MenuItems::eNum - 1)
			++mCurEntry;
	} else if (Input::IsKeyPressed(sf::Keyboard::Key::Enter)) {
		return ProcessEnter();
	}

	return true;
}

void MainMenuState::Update() {
	UpdateSizesAndPositions();
}

void MainMenuState::Render(sf::RenderTarget* const renderTarget) {
	renderTarget->draw(*mBgSprite);

	if (mGame.GetStateManager().GetCurrentState() == this) {
		for (auto& entry : mEntries)
			renderTarget->draw(entry);

		renderTarget->draw(*mIconSprite);
	}
}

bool MainMenuState::ProcessEnter() {
	switch (mCurEntry) {
	case MenuItems::eGameplay:
		mGame.GetStateManager().ClearAndSetState(std::make_unique<GameplayState>(mGame));
		break;

	case MenuItems::eOptions:
		mGame.GetStateManager().PushState(std::make_unique<OptionsMenuState>(mGame));
		break;

	case MenuItems::eCredits:
		mGame.GetStateManager().PushState(std::make_unique<CreditsMenuState>(mGame));
		break;

	case MenuItems::eExit:
		return false;
	}

	return true;
}

void MainMenuState::UpdateSizesAndPositions() {
	switch (mCurEntry) {
	case MenuItems::eGameplay:
		mIconSprite->setPosition({80.0f, 240.0f});

		mEntries[MenuItems::eGameplay].setScale({1.0f, 1.0f});
		mEntries[MenuItems::eGameplay].setPosition({280.0f, 220.0f});

		mEntries[MenuItems::eOptions].setScale({0.6f, 0.6f});
		mEntries[MenuItems::eOptions].setPosition({260.0f, 260.0f});

		mEntries[MenuItems::eCredits].setScale({0.6f, 0.6f});
		mEntries[MenuItems::eCredits].setPosition({250.0f, 330.0f});

		mEntries[MenuItems::eExit].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eExit].setPosition({310.0f, 440.0f});

		break;

	case MenuItems::eOptions:
		mIconSprite->setPosition({5.0f, 300.0f});

		mEntries[MenuItems::eGameplay].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eGameplay].setPosition({300.0f, 230.0f});

		mEntries[MenuItems::eOptions].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eOptions].setPosition({200.0f, 200.0f});

		mEntries[MenuItems::eCredits].setScale({0.6f, 0.6f});
		mEntries[MenuItems::eCredits].setPosition({250.0f, 330.0f});

		mEntries[MenuItems::eExit].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eExit].setPosition({310.0f, 440.0f});

		break;

	case MenuItems::eCredits:
		mIconSprite->setPosition({5.0f, 350.0f});

		mEntries[MenuItems::eGameplay].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eGameplay].setPosition({300.0f, 230.0f});

		mEntries[MenuItems::eOptions].setScale({0.6f, 0.6f});
		mEntries[MenuItems::eOptions].setPosition({260.0f, 240.0f});

		mEntries[MenuItems::eCredits].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eCredits].setPosition({210.0f, 260.0f});

		mEntries[MenuItems::eExit].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eExit].setPosition({310.0f, 440.0f});

		break;

	case MenuItems::eExit:
		mIconSprite->setPosition({80.0f, 440.0f});

		mEntries[MenuItems::eGameplay].setScale({0.8f, 0.8f});
		mEntries[MenuItems::eGameplay].setPosition({300.0f, 230.0f});

		mEntries[MenuItems::eOptions].setScale({0.6f, 0.6f});
		mEntries[MenuItems::eOptions].setPosition({260.0f, 260.0f});

		mEntries[MenuItems::eCredits].setScale({0.6f, 0.6f});
		mEntries[MenuItems::eCredits].setPosition({250.0f, 330.0f});

		mEntries[MenuItems::eExit].setScale({1.0f, 1.0f});
		mEntries[MenuItems::eExit].setPosition({300.0f, 420.0f});

		break;
	}
}
