#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <unordered_map>

class LuaState
{
public:
    LuaState() :
        mLuaState(luaL_newstate())
    {
        luaL_openlibs(mLuaState);
    }

    ~LuaState()
    {
        lua_close(mLuaState);
    }

    luabridge::LuaRef NewNilRef()
    {
        return luabridge::LuaRef(mLuaState);
    }

    luabridge::LuaRef NewTable()
    {
        return luabridge::newTable(mLuaState);
    }

    luabridge::LuaRef GetGlobal(const char* const name)
    {
        return luabridge::getGlobal(mLuaState, name);
    }

    luabridge::Namespace GetGlobalNamespace()
    {
        return luabridge::getGlobalNamespace(mLuaState);
    }

    template<class T>
    void SetGlobal(const char* const name, T obj)
    {
        luabridge::setGlobal(mLuaState, obj, name);
    }

    bool DoFile(const char* const file)
    {
        auto result = luaL_dofile(mLuaState, file);
        if (result != 0)
        {
            std::cout << "Lua DoFile error: " << lua_tostring(mLuaState, -1) << std::endl;
            return false;
        }

        return true;
    }

    luabridge::LuaRef CreateRefFromFile(const char* const file)
    {
        if (!DoFile(file))
            return NewNilRef();

        return luabridge::LuaRef::fromStack(mLuaState);
    }

    std::unordered_map<std::string, luabridge::LuaRef> GetKeyValueMap(luabridge::LuaRef table)
    {
        if (table.isNil())
            return {};

        std::error_code ec;
        if (!luabridge::push(mLuaState, table, ec))
        {
            std::cout << "GetKeyValueMap error: " << ec << std::endl;
            return {};
        }

        std::unordered_map<std::string, luabridge::LuaRef> result;
        lua_pushnil(mLuaState);
        while (lua_next(mLuaState, -2) != 0)
        {
            if (lua_isstring(mLuaState, -2))
                result.emplace(lua_tostring(mLuaState, -2), luabridge::LuaRef::fromStack(mLuaState, -1));
            lua_pop(mLuaState, 1);
        }
        lua_pop(mLuaState, 1);
        return result;
    }

private:
    lua_State* mLuaState;
};
