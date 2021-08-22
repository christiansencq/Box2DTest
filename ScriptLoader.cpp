#include "ScriptLoader.h"

ScriptLoader::ScriptLoader()
{
    

}

ScriptLoader::~ScriptLoader()
{

}

void ScriptLoader::GiveAppIntToLua(lua_State* L, int num)
{
    // lua_pushnumber(

}

bool ScriptLoader::LoadArenaData(std::string arena_data_file, ArenaLayoutData& arena)
{
    lua_State* L = luaL_newstate();
    // lua_checkstack(L, 50);
    luaL_openlibs(L);

    std::cout << "LOAD ARENA DATA \n";
    if(CheckLua(L, luaL_dofile(L, arena_data_file.c_str())))
    {
        std::cout << " - border\n";
        lua_getglobal(L, "Border");
        if (lua_istable(L, -1))
        {
            arena.WALL_THICKNESS = LuaKeyToFloat(L, "WallThickness");
            arena.WALL_BUFFER = LuaKeyToFloat(L, "WallBuffer");
        }

        std::cout << " - goalsize\n";
        lua_getglobal(L, "GoalSize");
        if (lua_istable(L, -1))
        {
            arena.GoalSize.x = LuaIndexToFloat(L, 1); 
            arena.GoalSize.y = LuaIndexToFloat(L, 2); 
        }

        std::cout << " - scoredisplaypos\n";
        lua_getglobal(L, "ScoreDisplayPos");
        if (lua_istable(L, -1))
        {
            b2Vec2 P1vec = LuaKeyTob2Vec(L, "P1");
            b2Vec2 P2vec = LuaKeyTob2Vec(L, "P2");
            arena.ScoreDisplayPositions.push_back(P1vec);
            arena.ScoreDisplayPositions.push_back(P2vec);
        }

        std::cout << " - goalpos\n";
        lua_getglobal(L, "GoalPositions");
        if (lua_istable(L, -1))
        {
            b2Vec2 P1GoalPos = LuaKeyTob2Vec(L, "P1");
            b2Vec2 P2GoalPos = LuaKeyTob2Vec(L, "P2");
            arena.GoalPositions.push_back(P1GoalPos);
            arena.GoalPositions.push_back(P2GoalPos);
        }

        std::cout << " - ballstartpos\n";
        lua_getglobal(L, "BallStartPos");
        if (lua_istable(L, -1))
        {
            LuaKeyToTable(L, "P1");

            b2Vec2 P1b1 = LuaKeyTob2Vec(L, "b1");
            b2Vec2 P1b2 = LuaKeyTob2Vec(L, "b2");
            b2Vec2 P1b3 = LuaKeyTob2Vec(L, "b3");

            arena.P1StartingPositions = { P1b1, P1b2, P1b3 };

            lua_pop(L, 1);

            LuaKeyToTable(L, "P2");

            b2Vec2 P2b1 = LuaKeyTob2Vec(L, "b1");
            b2Vec2 P2b2 = LuaKeyTob2Vec(L, "b2");
            b2Vec2 P2b3 = LuaKeyTob2Vec(L, "b3");
            
            arena.P2StartingPositions  = { P2b1, P2b2, P2b3 };
        }

        //Possibly move these to the Arena.
        //A CalculateValuesFromScriptData method:
        arena.TopWallSize = {SCREEN_WIDTH-70, arena.WALL_THICKNESS};
        arena.BottomWallSize = {SCREEN_WIDTH-70, arena.WALL_THICKNESS};
        arena.LeftWallSize = {arena.WALL_THICKNESS, SCREEN_HEIGHT-arena.WALL_BUFFER};
        arena.RightWallSize = {arena.WALL_THICKNESS, SCREEN_HEIGHT-arena.WALL_BUFFER};

        arena.WallSizes = {arena.TopWallSize, arena.BottomWallSize, arena.LeftWallSize, arena.RightWallSize};

        arena.GoalTopWallSize = { arena.GoalSize.x + (2 * arena.WALL_THICKNESS), arena.WALL_THICKNESS };
        arena.GoalBotWallSize = { arena.GoalSize.x + (2 * arena.WALL_THICKNESS), arena.WALL_THICKNESS };
        arena.GoalSideWallSize = { arena.WALL_THICKNESS, arena.GoalSize.y };
        arena.GoalWallSizes = { arena.GoalTopWallSize, arena.GoalBotWallSize, arena.GoalSideWallSize };

        std::cout << "Reading Goal Positions \n"; 
        arena.Goal1TopWallPos = { arena.GoalPositions[0].x, arena.GoalPositions[0].y - arena.GoalSize.y/2 };
        arena.Goal1BotWallPos = { arena.GoalPositions[0].x, arena.GoalPositions[0].y + arena.GoalSize.y/2 };
        arena.Goal1SideWallPos = { arena.GoalPositions[0].x + arena.GoalSize.x/2, arena.GoalPositions[0].y };
        arena.Goal1WallPositions = {arena.Goal1TopWallPos, arena.Goal1BotWallPos, arena.Goal1SideWallPos};
        
        arena.Goal2TopWallPos = { arena.GoalPositions[1].x, arena.GoalPositions[1].y - arena.GoalSize.y/2 };
        arena.Goal2BotWallPos = { arena.GoalPositions[1].x, arena.GoalPositions[1].y + arena.GoalSize.y/2 };
        arena.Goal2SideWallPos = { arena.GoalPositions[1].x - arena.GoalSize.x/2, arena.GoalPositions[1].y };
        arena.Goal2WallPositions = { arena.Goal2TopWallPos, arena.Goal2BotWallPos, arena.Goal2SideWallPos };
        arena.StartingPositions = {arena.P1StartingPositions, arena.P2StartingPositions};

        lua_close(L);
        std::cout << "DONE LOADING ARENA DATA\n";
        return true;
    }
    else
    {
        return false;
    }
}

bool ScriptLoader::CheckLua(lua_State* L, int r)
{
    if (r != LUA_OK)
    {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}

void ScriptLoader::LuaKeyToTable(lua_State* L, const char* key)
{
    lua_pushstring(L, key);
    lua_gettable(L, -2);
}

float ScriptLoader::LuaIndexToFloat(lua_State* L, int index)
{
    float num;

    lua_pushnumber(L, index);
    lua_gettable(L, -2);
    num = lua_tonumber(L, -1);
    lua_pop(L, 1);

    return num;
}

float ScriptLoader::LuaKeyToFloat(lua_State* L, const char* key)
{
    float num;
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    num = lua_tonumber(L, -1);
    lua_pop(L, 1);

    return num;
}

b2Vec2 ScriptLoader::LuaKeyTob2Vec(lua_State* L, const char* key)
{
    b2Vec2 point;
    lua_pushstring(L, key);
    lua_gettable(L, -2);

    std::cout << "loading " << key << "\n";
    point.x = LuaIndexToFloat(L, 1);
    point.y = LuaIndexToFloat(L, 2);
 
    std::cout << "loaded " << key << "\n";
    lua_pop(L, 1);

    return point;
}

bool ScriptLoader::LoadPlayerColorsFromFile(std::string colors_data_file, std::vector<Player>& players)
// bool ScriptLoader::LoadPlayerColorsFromFile(std::string colors_data_file, PlayerColorData& player_colors)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if(CheckLua(L, luaL_dofile(L, colors_data_file.c_str())))
    {
        lua_getglobal(L, "Player_Selector_Colors");
        if (lua_istable(L, -1))
        {
            for ( size_t i = 0; i < players.size(); i++)
            {
                // players[i].Colors.r = lua_to

            }
            
        }
    }

    return true;
}

