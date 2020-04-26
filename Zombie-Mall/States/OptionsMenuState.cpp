
#include "OptionsMenuState.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../Game.h"

#include "../Input/InputManager.h"

OptionsMenuState::OptionsMenuState(Game& game) :
    mEntries(),
    mCurEntry(0),
    mIcon(),
    mGame(game)
{}

OptionsMenuState::~OptionsMenuState() {}

void OptionsMenuState::Enter()
{
    mCurEntry = 0;

    auto font = mGame.GetFontManager().LoadFont("Resources/Fonts/FreeSans.ttf");
    if (font)
    {
        char buffer[32] = {};

        sprintf_s(buffer, "Music Volume: < %d >", mGame.GetSettings().GetMusicVolume());
        sf::Text text = sf::Text(buffer, *font);
        text.setPosition(300.0f, 400.0f);
        mEntries.push_back(text);

        sprintf_s(buffer, "Sfx Volume: < %d >", mGame.GetSettings().GetSfxVolume());
        text = sf::Text(buffer, *font);
        text.setPosition(300.0f, 450.0f);
        mEntries.push_back(text);

        text = sf::Text("Exit", *font);
        text.setPosition(300.0f, 500.0f);
        mEntries.push_back(text);
    }

    auto icon = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuPointer.png");
    if (icon)
    {
        mIcon.setTexture(*icon);
        mIcon.setScale(0.5f, 0.5f);
        mIcon.setPosition(150.0f, 350.0f);
    }
}

void OptionsMenuState::Exit()
{

}

bool OptionsMenuState::Input()
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
    else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Left))
    {
        DecreaseMenuItemValue();
    }
    else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Right))
    {
        IncreaseMenuItemValue();
    }
    else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Enter))
    {
        return ProcessEnter();
    }

    return true;
}

void OptionsMenuState::Update()
{
    mIcon.setPosition(150.0f, 350.0f + (mCurEntry * 50.0f));

    char buffer[32] = {};

    sprintf_s(buffer, "Music Volume: < %d >", mGame.GetSettings().GetMusicVolume());
    mEntries[MenuItems::MUSIC_VOLUME].setString(buffer);

    sprintf_s(buffer, "Sfx Volume: < %d >", mGame.GetSettings().GetSfxVolume());
    mEntries[MenuItems::SFX_VOLUME].setString(buffer);
}

void OptionsMenuState::Render(sf::RenderTarget* const renderTarget)
{
    for (auto& entry : mEntries)
        renderTarget->draw(entry);

    renderTarget->draw(mIcon);
}

bool OptionsMenuState::ProcessEnter()
{
    switch (mCurEntry)
    {
    case MenuItems::EXIT:
        mGame.GetStateManager().PopState();
        break;
    }

    return true;
}

void OptionsMenuState::DecreaseMenuItemValue()
{
    switch (mCurEntry)
    {
        case MenuItems::MUSIC_VOLUME:
        {
            auto& settings = mGame.GetSettings();
            settings.SetMusicVolume(settings.GetMusicVolume() - 1U);
        }
        break;

        case MenuItems::SFX_VOLUME:
        {
            auto& settings = mGame.GetSettings();
            settings.SetSfxVolume(settings.GetSfxVolume() - 1U);
        }
        break;
    }
}

void OptionsMenuState::IncreaseMenuItemValue()
{
    switch (mCurEntry)
    {
        case MenuItems::MUSIC_VOLUME:
        {
            auto& settings = mGame.GetSettings();
            settings.SetMusicVolume(settings.GetMusicVolume() + 1U);
        }
        break;

        case MenuItems::SFX_VOLUME:
        {
            auto& settings = mGame.GetSettings();
            settings.SetSfxVolume(settings.GetSfxVolume() + 1U);
        }
        break;
    }
}