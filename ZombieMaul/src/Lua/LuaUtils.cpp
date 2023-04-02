#include "LuaUtils.h"

#include <string>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Renderer/FontManager.h"
#include "Renderer/TextureManager.h"
#include "Input/InputManager.h"

LuaState LuaUtils::mLuaState;

void LuaUtils::LuaTableToSprite(luabridge::LuaRef table, sf::Sprite& sprite, TextureManager& textureManager)
{
    if (!table.isTable())
    {
        std::cout << "Passed in ref is not a table for sprite" << std::endl;
        return;
    }

    if (auto textureRef = table["texture"]; textureRef.isString())
    {
        auto texture = textureManager.LoadTexture(textureRef.cast<std::string>());
        if (texture)
            sprite.setTexture(*texture);
    }

    sprite.setPosition(LuaUtils::LuaTableToVec2(table["position"]));
    sprite.setScale(LuaUtils::LuaTableToVec2(table["scale"]));
}

void LuaUtils::LuaTableToText(luabridge::LuaRef table, sf::Text& text, FontManager& fontManager)
{
    if (!table.isTable())
    {
        std::cout << "Passed in ref is not a table for sprite" << std::endl;
        return;
    }

    if (auto fontRef = table["font"]; fontRef.isString())
    {
        auto font = fontManager.LoadFont(fontRef.cast<std::string>());
        if (font)
            text.setFont(*font);
    }

    if (auto textRef = table["text"]; textRef.isString())
    {
        const auto str = textRef.cast<std::string>();
        text.setString(sf::String::fromUtf8(std::cbegin(str), std::cend(str)));
    }

    text.setPosition(LuaUtils::LuaTableToVec2(table["position"]));
    text.setScale(LuaUtils::LuaTableToVec2(table["scale"]));
}

sf::Vector2f LuaUtils::LuaTableToVec2(luabridge::LuaRef table)
{
    if (!table.isTable())
    {
        std::cout << "Passed in ref is not a table for Vec2" << std::endl;
        return {};
    }

    sf::Vector2f vec;

    if (auto xRef = table["x"]; xRef.isNumber())
        vec.x = xRef.cast<float>();
    if (auto yRef = table["y"]; yRef.isNumber())
        vec.y = yRef.cast<float>();

    return vec;
}

void LuaUtils::BindLuaFuncs()
{
    mLuaState.GetGlobalNamespace()
        .addFunction("cout", &LuaUtils::Print)
        .addFunction("isKeyPressed", &LuaUtils::IsKeyPressed)
        .addFunction("isKeyDown", &LuaUtils::IsKeyDown)
        .addFunction("isKeyReleased", &LuaUtils::IsKeyReleased);
}

void LuaUtils::Print(const char* const s)
{
    std::cout << s << std::endl;
}

bool LuaUtils::IsKeyPressed(int key)
{
    return InputManager::Global.IsKeyPressed((sf::Keyboard::Key)key);
}

bool LuaUtils::IsKeyDown(int key)
{
    return InputManager::Global.IsKeyDown((sf::Keyboard::Key)key);
}

bool LuaUtils::IsKeyReleased(int key)
{
    return InputManager::Global.IsKeyReleased((sf::Keyboard::Key)key);
}
