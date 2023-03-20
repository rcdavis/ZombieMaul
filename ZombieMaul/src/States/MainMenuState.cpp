
#include "MainMenuState.h"

#include "../Game.h"

#include "../Input/InputManager.h"

#include "GameplayState.h"
#include "OptionsMenuState.h"
#include "CreditsMenuState.h"

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

    TextureManager& textureManager = mGame.GetTextureManager();
    auto texture = textureManager.LoadTexture("Resources/Textures/MenuPlay.png");
    if (texture)
        mEntries.emplace_back(*texture);

    texture = textureManager.LoadTexture("Resources/Textures/MenuOptions.png");
    if (texture)
        mEntries.emplace_back(*texture);

    texture = textureManager.LoadTexture("Resources/Textures/MenuCredits.png");
    if (texture)
        mEntries.emplace_back(*texture);

    texture = textureManager.LoadTexture("Resources/Textures/MenuExit.png");
    if (texture)
        mEntries.emplace_back(*texture);

    texture = textureManager.LoadTexture("Resources/Textures/MenuBG1.png");
    if (texture)
    {
        mBgImage.setTexture(*texture);
        mBgImage.setScale(0.8f, 0.75f);
        mBgImage.setPosition(0.0f, -20.0f);
    }

    auto icon = textureManager.LoadTexture("Resources/Textures/MenuPointer.png");
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

bool MainMenuState::Input()
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
        return ProcessEnter();
    }

    return true;
}

void MainMenuState::Update()
{
    UpdateSizesAndPositions();
}

void MainMenuState::Render(sf::RenderTarget* const renderTarget)
{
    renderTarget->draw(mBgImage);

    if (mGame.GetStateManager().GetCurrentState() == this)
    {
        for (auto& entry : mEntries)
            renderTarget->draw(entry);

        renderTarget->draw(mIcon);
    }
}

bool MainMenuState::ProcessEnter()
{
    switch (mCurEntry)
    {
    case MenuItems::GAMEPLAY:
        mGame.GetStateManager().ClearAndSetState(std::make_unique<GameplayState>(mGame));
        break;

    case MenuItems::OPTIONS:
        mGame.GetStateManager().PushState(std::make_unique<OptionsMenuState>(mGame));
        break;

    case MenuItems::CREDITS:
        mGame.GetStateManager().PushState(std::make_unique<CreditsMenuState>(mGame));
        break;

    case MenuItems::EXIT:
        return false;
    }

    return true;
}

void MainMenuState::UpdateSizesAndPositions()
{
    switch (mCurEntry)
    {
    case MenuItems::GAMEPLAY:
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

    case MenuItems::OPTIONS:
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

    case MenuItems::CREDITS:
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

    case MenuItems::EXIT:
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