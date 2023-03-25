#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Lua/LuaUtils.h"

#include <vector>
#include <string>

#include "IState.h"

class Game;

class MenuState : public IState
{
private:
    struct MenuEntry
    {
        sf::Sprite sprite;

        luabridge::LuaRef onClick;

        MenuEntry() :
            sprite(),
            onClick(LuaUtils::NewRef())
        {}

        MenuEntry(sf::Sprite sprite, luabridge::LuaRef onClick = LuaUtils::NewRef()) :
            sprite(sprite),
            onClick(onClick)
        {}
    };

public:
    MenuState(Game& game, const char* const file);
    ~MenuState();

    void Enter() override;
    void Exit() override;

    bool Input() override;
    void Update() override;
    void Render(sf::RenderTarget* const renderTarget) override;

    const char* GetName() const { return std::data(mName); }
    void SetName(const char* const name) { mName = name; }

    void SetBgPos(float x, float y) { mBg.setPosition(x, y); }
    void SetBgScale(float x, float y) { mBg.setScale(x, y); }

    void SetIconPos(float x, float y) { mIcon.setPosition(x, y); }
    void SetIconScale(float x, float y) { mIcon.setScale(x, y); }

    void SetEntryPos(int index, float x, float y) { mEntries[index].sprite.setPosition(x, y); }
    void SetEntryScale(int index, float x, float y) { mEntries[index].sprite.setScale(x, y); }

    static void BindLua();

private:
    bool ProcessEnter();
    void OnUpdateCurrentEntry();

private:
    std::string mName;
    std::string mSourceFile;

    sf::Sprite mBg;
    sf::Sprite mIcon;

    std::vector<MenuEntry> mEntries;
    std::size_t mCurEntry;

    luabridge::LuaRef mOnUpdate;
    luabridge::LuaRef mOnUpdateCurEntry;

    Game& mGame;
};
