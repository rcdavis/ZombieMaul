
#ifndef _LUAUTILS_H_
#define _LUAUTILS_H_

#include <SFML/System/Vector2.hpp>

#include "Lua/LuaState.h"

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

    static sf::Vector2f LuaTableToVec2(luabridge::LuaRef table)
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

private:
    static LuaState mLuaState;
};

#endif // !_LUAUTILS_H_
