
#include "MainMenuState.h"

#include "../Game.h"

#include "../Input/InputManager.h"

MainMenuState::MainMenuState(Game& game) :
	mBgImage(),
	mIcon(),
	mEntries(),
	mCurEntry(0),
	mGame(game)
{}

MainMenuState::~MainMenuState() {}

void MainMenuState::Enter()
{
	mCurEntry = 0;

	auto texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuPlay.png");
	if (texture)
		mEntries.push_back(sf::Sprite(*texture));

	texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuOptions.png");
	if (texture)
		mEntries.push_back(sf::Sprite(*texture));

	texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuCredits.png");
	if (texture)
		mEntries.push_back(sf::Sprite(*texture));

	texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuExit.png");
	if (texture)
		mEntries.push_back(sf::Sprite(*texture));

	texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuBG1.png");
	if (texture)
	{
		mBgImage.setTexture(*texture);
		mBgImage.setScale(0.8f, 0.75f);
		mBgImage.setPosition(0.0f, -20.0f);
	}

	auto icon = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuPointer.png");
	if (icon)
	{
		mIcon.setTexture(*icon);
		mIcon.setScale(0.8f, 0.8f);
	}
}

void MainMenuState::Exit()
{
	mEntries.clear();
}

void MainMenuState::Update()
{
	if (InputManager::Global.IsKeyPressed(sf::Keyboard::Up))
	{
		if (mCurEntry > 0)
			--mCurEntry;
	}
	else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Down))
	{
		if (mCurEntry < std::size(mEntries) - 1)
			++mCurEntry;
	}
	else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Enter))
	{
	}

	UpdateSizesAndPositions();
}

void MainMenuState::Render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(mBgImage);

	for (auto& entry : mEntries)
	{
		renderTarget->draw(entry);
	}

	renderTarget->draw(mIcon);
}

void MainMenuState::UpdateSizesAndPositions()
{
	switch (mCurEntry)
	{
	case 0:
		mIcon.setPosition(80.0f, 240.0f);

		mEntries[0].setScale(1.0f, 1.0f);
		mEntries[0].setPosition(280.0f, 220.0f);

		mEntries[1].setScale(0.6f, 0.6f);
		mEntries[1].setPosition(260.0f, 260.0f);
		
		mEntries[2].setScale(0.6f, 0.6f);
		mEntries[2].setPosition(250.0f, 330.0f);

		mEntries[3].setScale(0.8f, 0.8f);
		mEntries[3].setPosition(310.0f, 440.0f);

		break;

	case 1:
		mIcon.setPosition(5.0f, 300.0f);

		mEntries[0].setScale(0.8f, 0.8f);
		mEntries[0].setPosition(300.0f, 230.0f);

		mEntries[1].setScale(0.8f, 0.8f);
		mEntries[1].setPosition(200.0f, 200.0f);

		mEntries[2].setScale(0.6f, 0.6f);
		mEntries[2].setPosition(250.0f, 330.0f);

		mEntries[3].setScale(0.8f, 0.8f);
		mEntries[3].setPosition(310.0f, 440.0f);

		break;

	case 2:
		mIcon.setPosition(5.0f, 350.0f);

		mEntries[0].setScale(0.8f, 0.8f);
		mEntries[0].setPosition(300.0f, 230.0f);

		mEntries[1].setScale(0.6f, 0.6f);
		mEntries[1].setPosition(260.0f, 240.0f);

		mEntries[2].setScale(0.8f, 0.8f);
		mEntries[2].setPosition(210.0f, 260.0f);

		mEntries[3].setScale(0.8f, 0.8f);
		mEntries[3].setPosition(310.0f, 440.0f);

		break;

	case 3:
		mIcon.setPosition(80.0f, 440.0f);

		mEntries[0].setScale(0.8f, 0.8f);
		mEntries[0].setPosition(300.0f, 230.0f);

		mEntries[1].setScale(0.6f, 0.6f);
		mEntries[1].setPosition(260.0f, 260.0f);

		mEntries[2].setScale(0.6f, 0.6f);
		mEntries[2].setPosition(250.0f, 330.0f);

		mEntries[3].setScale(1.0f, 1.0f);
		mEntries[3].setPosition(300.0f, 420.0f);

		break;
	}
}