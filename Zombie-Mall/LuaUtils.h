
#ifndef _LUAUTILS_H_
#define _LUAUTILS_H_

#include <lua.hpp>
#include <LuaBridge.h>

class LuaUtils
{
public:
    static void Init()
    {
        mLuaState = luaL_newstate();
        luaL_openlibs(mLuaState);
    }

    static void Shutdown()
    {
        lua_close(mLuaState);
    }

    static luabridge::LuaRef NewRef()
    {
        return luabridge::LuaRef(mLuaState);
    }

    static luabridge::LuaRef NewTable()
    {
        return luabridge::newTable(mLuaState);
    }

    static luabridge::LuaRef GetGlobal(const char* name)
    {
        return luabridge::getGlobal(mLuaState, name);
    }

    static luabridge::Namespace GetGlobalNamespace()
    {
        return luabridge::getGlobalNamespace(mLuaState);
    }

    template<class T>
    static void SetGlobal(const char* name, T obj)
    {
        luabridge::setGlobal(mLuaState, obj, name);
    }

    static bool DoFile(const char* name)
    {
        return luaL_dofile(mLuaState, name) == 0;
    }

private:
    static lua_State* mLuaState;
};

lua_State* LuaUtils::mLuaState = nullptr;

#endif // !_LUAUTILS_H_