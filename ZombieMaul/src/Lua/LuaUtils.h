
#ifndef _LUAUTILS_H_
#define _LUAUTILS_H_

#include <SFML/System/Vector2.hpp>

#include "Lua/LuaState.h"

namespace sf
{
    class Sprite;
    class Text;
}

class TextureManager;
class FontManager;

class LuaUtils
{
public:
    static luabridge::LuaRef NewRef()
    {
        return mLuaState.NewNilRef();
    }

    static luabridge::LuaRef NewTable()
    {
        return mLuaState.NewTable();
    }

    static luabridge::LuaRef GetGlobal(const char* const name)
    {
        return mLuaState.GetGlobal(name);
    }

    static luabridge::Namespace GetGlobalNamespace()
    {
        return mLuaState.GetGlobalNamespace();
    }

    template<class T>
    static void SetGlobal(const char* const name, T obj)
    {
        mLuaState.SetGlobal(name, obj);
    }

    static bool DoFile(const char* const file)
    {
        return mLuaState.DoFile(file);
    }

    static luabridge::LuaRef CreateRefFromFile(const char* const file)
    {
        return mLuaState.CreateRefFromFile(file);
    }

    static std::unordered_map<std::string, luabridge::LuaRef> GetKeyValueMap(luabridge::LuaRef table)
    {
        return mLuaState.GetKeyValueMap(table);
    }

    static void LuaTableToSprite(luabridge::LuaRef table, sf::Sprite& sprite, TextureManager& textureManager);
    static void LuaTableToText(luabridge::LuaRef table, sf::Text& text, FontManager& fontManager);
    static sf::Vector2f LuaTableToVec2(luabridge::LuaRef table);

private:
    static LuaState mLuaState;
};

#endif // !_LUAUTILS_H_
