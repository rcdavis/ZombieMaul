#include "States/MainMenuState.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Renderer/TextureManager.h"
#include "Game.h"

MainMenuState::MainMenuState(Game& game) :
	mEntries(),
	mBgSprite(),
	mIconSprite(),
	mGame(game),
	mCurEntry(MenuItems::Gameplay)
{}

MainMenuState::~MainMenuState() {}

void MainMenuState::Enter() {
	mCurEntry = MenuItems::Gameplay;

	sf::Texture* tex = TextureManager::LoadTexture("res/textures/MenuBG1.png");
	if (tex) {
		mBgSprite = std::make_unique<sf::Sprite>(*tex);
		mBgSprite->setScale({0.8f, 0.75f});
		mBgSprite->setPosition({0.0f, -20.0f});
	}

	tex = TextureManager::LoadTexture("res/textures/MenuPointer.png");
	if (tex) {
		mIconSprite = std::make_unique<sf::Sprite>(*tex);
		mIconSprite->setScale({0.8f, 0.8f});
	}

	tex = TextureManager::LoadTexture("res/textures/MenuPlay.png");
	if (tex)
		mEntries.push_back(std::make_unique<sf::Sprite>(*tex));

	tex = TextureManager::LoadTexture("res/textures/MenuOptions.png");
	if (tex)
		mEntries.push_back(std::make_unique<sf::Sprite>(*tex));

	tex = TextureManager::LoadTexture("res/textures/MenuCredits.png");
	if (tex)
		mEntries.push_back(std::make_unique<sf::Sprite>(*tex));

	tex = TextureManager::LoadTexture("res/textures/MenuExit.png");
	if (tex)
		mEntries.push_back(std::make_unique<sf::Sprite>(*tex));
}

void MainMenuState::Exit() {
	mEntries.clear();
	mBgSprite = nullptr;
	mIconSprite = nullptr;
}

bool MainMenuState::Input() {
	return true;
}

void MainMenuState::Update() {
	UpdateSizesAndPositions();
}

void MainMenuState::Render(sf::RenderTarget* const renderTarget) {
	renderTarget->draw(*mBgSprite);

	if (mGame.GetStateManager().GetCurrentState() == this) {
		for (auto& entry : mEntries)
			renderTarget->draw(*entry);

		renderTarget->draw(*mIconSprite);
	}
}

bool MainMenuState::ProcessEnter() {
	switch (mCurEntry) {
	case MenuItems::Gameplay:
		//mGame.GetStateManager().ClearAndSetState(std::make_unique<GameplayState>(mGame));
		break;

	case MenuItems::Options:
		//mGame.GetStateManager().PushState(std::make_unique<OptionsMenuState>(mGame));
		break;

	case MenuItems::Credits:
		//mGame.GetStateManager().PushState(std::make_unique<CreditsMenuState>(mGame));
		break;

	case MenuItems::Exit:
		return false;
	}

	return true;
}

void MainMenuState::UpdateSizesAndPositions() {
	switch (mCurEntry) {
	case MenuItems::Gameplay:
		mIconSprite->setPosition({80.0f, 240.0f});

		mEntries[0]->setScale({1.0f, 1.0f});
		mEntries[0]->setPosition({280.0f, 220.0f});

		mEntries[1]->setScale({0.6f, 0.6f});
		mEntries[1]->setPosition({260.0f, 260.0f});

		mEntries[2]->setScale({0.6f, 0.6f});
		mEntries[2]->setPosition({250.0f, 330.0f});

		mEntries[3]->setScale({0.8f, 0.8f});
		mEntries[3]->setPosition({310.0f, 440.0f});

		break;

	case MenuItems::Options:
		mIconSprite->setPosition({5.0f, 300.0f});

		mEntries[0]->setScale({0.8f, 0.8f});
		mEntries[0]->setPosition({300.0f, 230.0f});

		mEntries[1]->setScale({0.8f, 0.8f});
		mEntries[1]->setPosition({200.0f, 200.0f});

		mEntries[2]->setScale({0.6f, 0.6f});
		mEntries[2]->setPosition({250.0f, 330.0f});

		mEntries[3]->setScale({0.8f, 0.8f});
		mEntries[3]->setPosition({310.0f, 440.0f});

		break;

	case MenuItems::Credits:
		mIconSprite->setPosition({5.0f, 350.0f});

		mEntries[0]->setScale({0.8f, 0.8f});
		mEntries[0]->setPosition({300.0f, 230.0f});

		mEntries[1]->setScale({0.6f, 0.6f});
		mEntries[1]->setPosition({260.0f, 240.0f});

		mEntries[2]->setScale({0.8f, 0.8f});
		mEntries[2]->setPosition({210.0f, 260.0f});

		mEntries[3]->setScale({0.8f, 0.8f});
		mEntries[3]->setPosition({310.0f, 440.0f});

		break;

	case MenuItems::Exit:
		mIconSprite->setPosition({80.0f, 440.0f});

		mEntries[0]->setScale({0.8f, 0.8f});
		mEntries[0]->setPosition({300.0f, 230.0f});

		mEntries[1]->setScale({0.6f, 0.6f});
		mEntries[1]->setPosition({260.0f, 260.0f});

		mEntries[2]->setScale({0.6f, 0.6f});
		mEntries[2]->setPosition({250.0f, 330.0f});

		mEntries[3]->setScale({1.0f, 1.0f});
		mEntries[3]->setPosition({300.0f, 420.0f});

		break;
	}
}
