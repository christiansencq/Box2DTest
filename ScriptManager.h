#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "Box2D/Box2D.h"
#include "lua.hpp"


static struct Arena
{
    float WALL_THICKNESS;
    float WALL_BUFFER;
    float GOAL_WIDTH;
    float GOAL_HEIGHT;
    b2Vec2 GoalSize;
} arena;

class ScriptManager
{
public:
    ScriptManager();
    ~ScriptManager();

    bool LoadArenaData(std::string arena_data_file);
    void LoadArenaData();

private:

    bool CheckLua(lua_State* L, int r);

};

#endif
