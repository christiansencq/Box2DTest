#include "ScriptManager.h"

ScriptManager::ScriptManager()
{
    
    LoadArenaData();

}

ScriptManager::~ScriptManager()
{

}

void ScriptManager::LoadArenaData()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if(CheckLua(L, luaL_dofile(L, "script.lua")))
    {
        /*
            Look for an item named 'arena'
            Push the contents on top the of the stack.
            Then, pull the top contents and assign them to whatever variable we want.
            Last, we can discard the top element, so the next item can be put there.
        */

        lua_getglobal(L, "arena");

        if (lua_istable(L, -1))
        {
            lua_pushstring(L, "WallThickness");
            lua_gettable(L, -2);
            arena.WALL_THICKNESS = lua_tonumber(L, -1);
            std::cout << "arena WT " << arena.WALL_THICKNESS << "\n";
            lua_pop(L, 1);

            lua_pushstring(L, "WallBuffer");
            lua_gettable(L, -2);
            arena.WALL_BUFFER = lua_tonumber(L, -1);
            std::cout << "arena WB " << arena.WALL_BUFFER << "\n";
            lua_pop(L, 1);

            lua_pushstring(L, "GoalWidth");
            lua_gettable(L, -2);
            arena.GOAL_WIDTH = lua_tonumber(L, -1);
            std::cout << "arena GW " << arena.GOAL_WIDTH << "\n";
            lua_pop(L, 1);

            lua_pushstring(L, "GoalHeight");
            lua_gettable(L, -2);
            arena.GOAL_HEIGHT = lua_tonumber(L, -1);
            std::cout << "arena GH " << arena.GOAL_HEIGHT << "\n";
            lua_pop(L, 1);
        }
    }
    
    lua_close(L);
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

