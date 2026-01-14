#include "States/MainMenuState.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Renderer/TextureManager.h"
#include "Input/Input.h"
#include "Game.h"

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

	sf::Texture* tex = TextureManager::LoadTexture("res/textures/MenuBG1.png");
	if (tex) {
		tex->setSmooth(true);
		mBgSprite.emplace(*tex);
		mBgSprite->setScale({0.8f, 0.75f});
		mBgSprite->setPosition({0.0f, -20.0f});
	}

	tex = TextureManager::LoadTexture("res/textures/MenuPointer.png");
	if (tex) {
		tex->setSmooth(true);
		mIconSprite.emplace(*tex);
		mIconSprite->setScale({0.8f, 0.8f});
	}

	mEntries.reserve(MenuItems::Num);
	tex = TextureManager::LoadTexture("res/textures/MenuPlay.png");
	if (tex) {
		tex->setSmooth(true);
		mEntries.emplace_back(*tex);
	}

	tex = TextureManager::LoadTexture("res/textures/MenuOptions.png");
	if (tex) {
		tex->setSmooth(true);
		mEntries.emplace_back(*tex);
	}

	tex = TextureManager::LoadTexture("res/textures/MenuCredits.png");
	if (tex) {
		tex->setSmooth(true);
		mEntries.emplace_back(*tex);
	}

	tex = TextureManager::LoadTexture("res/textures/MenuExit.png");
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
		if (mCurEntry < MenuItems::Num - 1)
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
	case MenuItems::Gameplay:
		mGame.GetStateManager().ClearAndSetState(std::make_unique<GameplayState>(mGame));
		break;

	case MenuItems::Options:
		mGame.GetStateManager().PushState(std::make_unique<OptionsMenuState>(mGame));
		break;

	case MenuItems::Credits:
		mGame.GetStateManager().PushState(std::make_unique<CreditsMenuState>(mGame));
		break;

	case MenuItems::Quit:
		return false;
	}

	return true;
}

void MainMenuState::UpdateSizesAndPositions() {
	switch (mCurEntry) {
	case MenuItems::Gameplay:
		mIconSprite->setPosition({80.0f, 240.0f});

		mEntries[MenuItems::Gameplay].setScale({1.0f, 1.0f});
		mEntries[MenuItems::Gameplay].setPosition({280.0f, 220.0f});

		mEntries[MenuItems::Options].setScale({0.6f, 0.6f});
		mEntries[MenuItems::Options].setPosition({260.0f, 260.0f});

		mEntries[MenuItems::Credits].setScale({0.6f, 0.6f});
		mEntries[MenuItems::Credits].setPosition({250.0f, 330.0f});

		mEntries[MenuItems::Quit].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Quit].setPosition({310.0f, 440.0f});

		break;

	case MenuItems::Options:
		mIconSprite->setPosition({5.0f, 300.0f});

		mEntries[MenuItems::Gameplay].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Gameplay].setPosition({300.0f, 230.0f});

		mEntries[MenuItems::Options].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Options].setPosition({200.0f, 200.0f});

		mEntries[MenuItems::Credits].setScale({0.6f, 0.6f});
		mEntries[MenuItems::Credits].setPosition({250.0f, 330.0f});

		mEntries[MenuItems::Quit].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Quit].setPosition({310.0f, 440.0f});

		break;

	case MenuItems::Credits:
		mIconSprite->setPosition({5.0f, 350.0f});

		mEntries[MenuItems::Gameplay].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Gameplay].setPosition({300.0f, 230.0f});

		mEntries[MenuItems::Options].setScale({0.6f, 0.6f});
		mEntries[MenuItems::Options].setPosition({260.0f, 240.0f});

		mEntries[MenuItems::Credits].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Credits].setPosition({210.0f, 260.0f});

		mEntries[MenuItems::Quit].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Quit].setPosition({310.0f, 440.0f});

		break;

	case MenuItems::Quit:
		mIconSprite->setPosition({80.0f, 440.0f});

		mEntries[MenuItems::Gameplay].setScale({0.8f, 0.8f});
		mEntries[MenuItems::Gameplay].setPosition({300.0f, 230.0f});

		mEntries[MenuItems::Options].setScale({0.6f, 0.6f});
		mEntries[MenuItems::Options].setPosition({260.0f, 260.0f});

		mEntries[MenuItems::Credits].setScale({0.6f, 0.6f});
		mEntries[MenuItems::Credits].setPosition({250.0f, 330.0f});

		mEntries[MenuItems::Quit].setScale({1.0f, 1.0f});
		mEntries[MenuItems::Quit].setPosition({300.0f, 420.0f});

		break;
	}
}
