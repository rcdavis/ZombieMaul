
#include "MenuState.h"

#include "../Game.h"

#include "../Input/InputManager.h"

#include "GameplayState.h"
#include "OptionsMenuState.h"
#include "CreditsMenuState.h"

MenuState::MenuState(Game& game, const char* const file) :
    mName(),
    mSourceFile(file),
    mBg(),
    mIcon(),
    mEntries(),
    mCurEntry(0),
    mOnUpdate(LuaUtils::NewRef()),
    mOnUpdateCurEntry(LuaUtils::NewRef()),
    mGame(game)
{}

MenuState::~MenuState() {}

void MenuState::Enter()
{
    TextureManager& textureManager = mGame.GetTextureManager();
    FontManager& fontManager = mGame.GetFontManager();

    mCurEntry = 0;

    auto table = LuaUtils::CreateRefFromFile(std::data(mSourceFile));
    if (!table.isTable())
    {
        std::cout << "Couldn't get lua table for " << mSourceFile << std::endl;
        return;
    }

    if (auto name = table["name"]; name.isString())
        mName = name.cast<std::string>();

    if (auto callback = table["onUpdate"]; callback.isCallable())
        mOnUpdate = callback;

    if (auto callback = table["onUpdateCurrentEntry"]; callback.isCallable())
        mOnUpdateCurEntry = callback;

    LuaUtils::LuaTableToSprite(table["background"], mBg, textureManager);
    LuaUtils::LuaTableToSprite(table["icon"], mIcon, textureManager);

    if (auto entries = table["entries"]; entries.isTable())
    {
        for (int i = 1; i <= entries.length(); ++i)
        {
            MenuEntry menuEntry;
            auto entry = entries[i];

            if (auto spriteRef = entry["texture"]; spriteRef.isString())
                menuEntry.hasSprite = true;

            if (menuEntry.hasSprite)
                LuaUtils::LuaTableToSprite(entry, menuEntry.sprite, textureManager);
            else
                LuaUtils::LuaTableToText(entry, menuEntry.text, fontManager);

            if (auto onClick = entry["onClick"]; onClick.isCallable())
                menuEntry.onClick = onClick;

            mEntries.push_back(menuEntry);
        }
    }
}

void MenuState::Exit()
{
    mEntries.clear();
}

bool MenuState::Input()
{
    if (InputManager::Global.IsKeyPressed(sf::Keyboard::Up))
    {
        if (mCurEntry > 0)
        {
            --mCurEntry;
            OnUpdateCurrentEntry();
        }
    }
    else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Down))
    {
        if (mCurEntry < std::size(mEntries) - 1)
        {
            ++mCurEntry;
            OnUpdateCurrentEntry();
        }
    }
    else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Enter))
    {
        return ProcessEnter();
    }

    return true;
}

void MenuState::Update()
{
    try
    {
        if (mOnUpdate.isCallable())
            mOnUpdate(this, mCurEntry);
    }
    catch (const luabridge::LuaException& e)
    {
        std::cout << "MenuState(" << mName << ")::Update error: " << e.what() << std::endl;
    }
}

void MenuState::Render(sf::RenderTarget* const renderTarget)
{
    renderTarget->draw(mBg);

    if (mGame.GetStateManager().GetCurrentState() == this)
    {
        for (auto& entry : mEntries)
        {
            if (entry.hasSprite)
                renderTarget->draw(entry.sprite);
            else
                renderTarget->draw(entry.text);
        }

        renderTarget->draw(mIcon);
    }
}

bool MenuState::ProcessEnter()
{
    try
    {
        if (mEntries[mCurEntry].onClick.isCallable())
        {
            auto result = mEntries[mCurEntry].onClick();
            if (!result)
            {
                std::cout << "onClick error: " << result.errorMessage() << std::endl;
                return false;
            }

            return result[0].cast<bool>();
        }
    }
    catch (const luabridge::LuaException& e)
    {
        std::cout << "MenuEntry::onClick error for entry " << mCurEntry << ": " << e.what() << std::endl;
    }

    return true;
}

void MenuState::OnUpdateCurrentEntry()
{
    try
    {
        if (mOnUpdateCurEntry.isCallable())
            mOnUpdateCurEntry(this, mCurEntry);
    }
    catch (const luabridge::LuaException& e)
    {
        std::cout << "MenuState(" << mName << ")::UpdateCurEntry error "
            << mCurEntry << ": " << e.what() << std::endl;
    }
}

void MenuState::BindLua()
{
    LuaUtils::GetGlobalNamespace()
        .beginClass<MenuState>("MenuState")
            .addProperty("name", &MenuState::GetName, &MenuState::SetName)
            .addFunction("setBgPos", &MenuState::SetBgPos)
            .addFunction("setBgScale", &MenuState::SetBgScale)
            .addFunction("setIconPos", &MenuState::SetIconPos)
            .addFunction("setIconScale", &MenuState::SetIconScale)
            .addFunction("setEntryText", &MenuState::SetEntryText)
            .addFunction("setEntryPos", &MenuState::SetEntryPos)
            .addFunction("setEntryScale", &MenuState::SetEntryScale)
        .endClass();
}
