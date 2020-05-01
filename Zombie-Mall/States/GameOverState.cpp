
#include "GameOverState.h"

#include "MainMenuState.h"

#include "../Game.h"
#include "../Input/InputManager.h"

GameOverState::GameOverState(Game& game) :
    mEntries(),
    mBgImage(),
    mGame(game)
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::Enter()
{
    auto font = mGame.GetFontManager().LoadFont("Resources/Fonts/FreeSans.ttf");
    if (font)
    {
        AddTextEntry("Game Over", font, sf::Vector2f(300.0f, 400.0f));

        char buffer[16] = {};
        sprintf_s(buffer, "Score: %i", mGame.GetScore());
        AddTextEntry(buffer, font, sf::Vector2f(300.0f, 500.0f));
    }

    auto texture = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuBG1.png");
    if (texture)
    {
        mBgImage.setTexture(*texture);
        mBgImage.setScale(0.8f, 0.75f);
        mBgImage.setPosition(0.0f, -20.0f);
    }
}

void GameOverState::Exit()
{
    mEntries.clear();
}

bool GameOverState::Input()
{
    if (InputManager::Global.IsKeyPressed(sf::Keyboard::Enter))
    {
        mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));
    }

    return true;
}

void GameOverState::Update()
{
    
}

void GameOverState::Render(sf::RenderTarget* const renderTarget)
{
    renderTarget->draw(mBgImage);

    for (auto& entry : mEntries)
        renderTarget->draw(entry);
}

void GameOverState::AddTextEntry(const std::string& str, sf::Font* font, sf::Vector2f pos)
{
    sf::Text text(str, *font);
    text.setPosition(pos);
    mEntries.push_back(text);
}