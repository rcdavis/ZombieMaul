
#include "MenuState.h"

#include "../Game.h"

#include "../Input/InputManager.h"

#include "GameplayState.h"
#include "OptionsMenuState.h"
#include "CreditsMenuState.h"

MenuState::MenuState(Game& game, const char* const file) :
    mName(),
    mBg(),
    mIcon(),
    mEntries(),
    mCurEntry(0),
    mTable(LuaUtils::CreateRefFromFile(file)),
    mGame(game)
{}

MenuState::~MenuState() {}

void MenuState::Enter()
{
    TextureManager& textureManager = mGame.GetTextureManager();

    mCurEntry = 0;

    if (auto name = mTable["name"]; name.isString())
        mName = name.cast<std::string>();

    if (auto bg = mTable["background"]; bg.isTable())
    {
        if (auto textureRef = bg["texture"]; textureRef.isString())
        {
            auto texture = textureManager.LoadTexture(textureRef.cast<std::string>());
            if (texture)
                mBg.setTexture(*texture);
        }

        mBg.setPosition(LuaUtils::LuaTableToVec2(bg["position"]));
        mBg.setScale(LuaUtils::LuaTableToVec2(bg["scale"]));
    }

    if (auto icon = mTable["icon"]; icon.isTable())
    {
        if (auto textureRef = icon["texture"]; textureRef.isString())
        {
            auto texture = textureManager.LoadTexture(textureRef.cast<std::string>());
            if (texture)
                mIcon.setTexture(*texture);
        }

        mIcon.setPosition(LuaUtils::LuaTableToVec2(icon["position"]));
        mIcon.setScale(LuaUtils::LuaTableToVec2(icon["scale"]));
    }

    if (auto entries = mTable["entries"]; entries.isTable())
    {
        for (int i = 0; i < entries.length(); ++i)
        {
            MenuEntry menuEntry;
            auto entry = entries[i + 1];
            if (auto textureRef = entry["texture"]; textureRef.isString())
            {
                auto texture = textureManager.LoadTexture(textureRef.cast<std::string>());
                if (texture)
                    menuEntry.sprite.setTexture(*texture);
            }

            menuEntry.sprite.setPosition(LuaUtils::LuaTableToVec2(entry["position"]));
            menuEntry.sprite.setScale(LuaUtils::LuaTableToVec2(entry["scale"]));

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
    if (InputManager::Global.IsKeyPressed(sf::Keyboard::Up) || InputManager::Global.IsKeyPressed(sf::Keyboard::Left))
    {
        if (mCurEntry > 0)
            --mCurEntry;
    }
    else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Down) || InputManager::Global.IsKeyPressed(sf::Keyboard::Right))
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

void MenuState::Update()
{
    if (mTable)
    {
        try
        {
            if (auto onUpdate = mTable["onUpdate"]; onUpdate.isCallable())
                onUpdate(mTable, mCurEntry);
        }
        catch (const luabridge::LuaException& e)
        {
            std::cout << "MenuState(" << mName << ")::Update error: " << e.what() << std::endl;
        }
    }
}

void MenuState::Render(sf::RenderTarget* const renderTarget)
{
    renderTarget->draw(mBg);

    if (mGame.GetStateManager().GetCurrentState() == this)
    {
        for (auto& entry : mEntries)
            renderTarget->draw(entry.sprite);

        renderTarget->draw(mIcon);
    }
}

bool MenuState::ProcessEnter()
{
    try
    {
        if (mEntries[mCurEntry].onClick.isCallable())
            mEntries[mCurEntry].onClick();
    }
    catch (const luabridge::LuaException& e)
    {
        std::cout << "MenuEntry::onClick error for entry " << mCurEntry << ": " << e.what() << std::endl;
    }

    return true;
}

void MenuState::BindLua()
{
    LuaUtils::GetGlobalNamespace()
        .beginClass<MenuState>("MenuState")
            //.addConstructor<void(*)(void)>()
            .addProperty("name", &MenuState::GetName, &MenuState::SetName)
            .addFunction("setBgPos", &MenuState::SetBgPos)
            .addFunction("setBgScale", &MenuState::SetBgScale)
            .addFunction("setIconPos", &MenuState::SetIconPos)
            .addFunction("setIconScale", &MenuState::SetIconScale)
        .endClass();
}
