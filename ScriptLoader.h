#ifndef SCRIPT_LOADER_H
#define SCRIPT_LOADER_H

#include <iostream>
#include <string>
#include <vector>

#include "Box2D/Box2D.h"
#include "lua.hpp"

#include "Colors.h"
#include "ArenaLayout.h"

#include "Player.h"

class ScriptLoader
{
public:
    ScriptLoader();
    ~ScriptLoader();

    bool LoadArenaData(std::string arena_data_file, ArenaLayoutData& arena);

private:
    //This just exists to be moved later.
    void CalcArenaData();

    bool LoadPlayerColorsFromFile(std::string colors_data_file, std::vector<Player>& players); 

    bool CheckLua(lua_State* L, int r);

    //This will be used to send Input from the App (like Screen Size, SDL_Keys etc) to the Lua Script. Call it first thing.
    void GiveAppIntToLua(lua_State* L, int num);

    //Utility
    float LuaIndexToFloat(lua_State* L, int index);


    void LuaKeyToTable(lua_State* L, const char* key);
    float LuaKeyToFloat(lua_State* L, const char* key);
    b2Vec2 LuaKeyTob2Vec(lua_State* L, const char* key);

};

#endif
