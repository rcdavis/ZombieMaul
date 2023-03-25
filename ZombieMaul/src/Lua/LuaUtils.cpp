#include "LuaUtils.h"

#include <string>

#include <SFML/Graphics/Sprite.hpp>

#include "Renderer/TextureManager.h"

LuaState LuaUtils::mLuaState;

void LuaUtils::LuaTableToSprite(luabridge::LuaRef table, sf::Sprite& sprite, TextureManager& textureManager)
{
    if (table.isTable())
    {
        if (auto textureRef = table["texture"]; textureRef.isString())
        {
            auto texture = textureManager.LoadTexture(textureRef.cast<std::string>());
            if (texture)
                sprite.setTexture(*texture);
        }

        sprite.setPosition(LuaUtils::LuaTableToVec2(table["position"]));
        sprite.setScale(LuaUtils::LuaTableToVec2(table["scale"]));
    }
}

sf::Vector2f LuaUtils::LuaTableToVec2(luabridge::LuaRef table)
{
    sf::Vector2f vec;
    if (table.isTable())
    {
        if (auto xRef = table["x"]; xRef.isNumber())
            vec.x = xRef.cast<float>();
        if (auto yRef = table["y"]; yRef.isNumber())
            vec.y = yRef.cast<float>();
    }
    return vec;
}
