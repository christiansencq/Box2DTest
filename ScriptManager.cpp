#include "ScriptManager.h"

ScriptManager::ScriptManager()
{
    

}

ScriptManager::~ScriptManager()
{

}


bool ScriptManager::LoadArenaData(std::string arena_data_file)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if(CheckLua(L, luaL_dofile(L, arena_data_file.c_str())))
    {
        //Look for a Function?
        lua_getglobal(L, "SetArena");
        //Check that the top object on the stack is a function.
        if (lua_isfunction(L, -1))
        {
            //pcall catches thrown exceptions from lua code.
            if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
            {
                std::cout << "From C++, called SetArena \n";

                if (lua_istable(L, -1))
                {
                    lua_pushstring(L, "WALL_THICKNESS");
                    lua_gettable(L, -2);
                    arena.WALL_THICKNESS = lua_tonumber(L, -1);
                    lua_pop(L, 1);

                    lua_pushstring(L, "WALL_BUFFER");
                    lua_gettable(L, -2);
                    arena.WALL_BUFFER = lua_tonumber(L, -1);
                    lua_pop(L, 1);

                    lua_pushstring(L, "GoalWidth");
                    lua_gettable(L, -2);
                    arena.GOAL_WIDTH = lua_tonumber(L, -1);
                    lua_pop(L, 1);

                    lua_pushstring(L, "GoalWidth");
                    lua_gettable(L, -2);
                    arena.GOAL_HEIGHT = lua_tonumber(L, -1);
                    lua_pop(L, 1);
                }
            }

        }
        lua_close(L);
        return true;
    }
    else
    {
        return false;
    }
}

bool ScriptManager::CheckLua(lua_State* L, int r)
{
    if (r != LUA_OK)
    {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}

