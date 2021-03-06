#include "ScriptLoader.h"

ScriptLoader::ScriptLoader()
{
}

ScriptLoader::~ScriptLoader()
{
}

void ScriptLoader::SolLoadArenaData(std::string arena_data_file, ArenaLayoutData& arena)
{
    sol::state lua{};
    lua.open_libraries(sol::lib::base); lua.script_file(arena_data_file.c_str());
    std::cout << "Opened File for Arena Data\n";

    std::cout << "Loading Wall Variables\n";
    arena.WALL_THICKNESS = lua["Border"]["WallThickness"];
    arena.WALL_BUFFER = lua["Border"]["WallBuffer"];

    std::cout << "Loading GoalSize Variables\n";
    arena.GoalSize.x = lua["GoalSize"][1];
    arena.GoalSize.y = lua["GoalSize"][2];

    std::cout << "Loading ScoreDisplay Position\n";
    b2Vec2 p1scorepos = { lua["ScoreDisplayPos"]["P1"][1], lua["ScoreDisplayPos"]["P1"][2] };
    b2Vec2 p2scorepos = { lua["ScoreDisplayPos"]["P2"][1], lua["ScoreDisplayPos"]["P2"][2] };

    std::cout << "Loading GoalDisplay Position\n";
    b2Vec2 p1goalpos = { lua["GoalDisplayPos"]["P1"][1], lua["GoalDisplayPos"]["P1"][2] };
    b2Vec2 p2goalpos = { lua["GoalDisplayPos"]["P2"][1], lua["GoalDisplayPos"]["P2"][2] };

    std::cout << "Adding Score and Goal Pos to the Arena\n";
    arena.ScoreDisplayPositions.push_back(p1scorepos);
    arena.ScoreDisplayPositions.push_back(p2scorepos);
    arena.GoalPositions.push_back(p1goalpos);
    arena.GoalPositions.push_back(p2goalpos);

    std::cout << "Loading StartPositions for P1\n";
    b2Vec2 P1b1 = { lua["BallStartPos"]["P1"]["b1"][1], 
                    lua["BallStartPos"]["P1"]["b1"][2] };
    b2Vec2 P1b2 = { lua["BallStartPos"]["P1"]["b2"][1], 
                    lua["BallStartPos"]["P1"]["b2"][2] };
    b2Vec2 P1b3 = { lua["BallStartPos"]["P1"]["b3"][1], 
                    lua["BallStartPos"]["P1"]["b3"][2] };
    std::cout << "Loading StartPositions for P2\n";
    b2Vec2 P2b1 = { lua["BallStartPos"]["P2"]["b1"][1], 
                    lua["BallStartPos"]["P2"]["b1"][2] };
    b2Vec2 P2b2 = { lua["BallStartPos"]["P2"]["b2"][1], 
                    lua["BallStartPos"]["P2"]["b2"][2] };
    b2Vec2 P2b3 = { lua["BallStartPos"]["P2"]["b3"][1], 
                    lua["BallStartPos"]["P2"]["b3"][2] };

    arena.P1StartingPositions = { P1b1, P1b2, P1b3 };
    arena.P2StartingPositions = { P2b1, P2b2, P2b3 };
    
    CalcArenaData(arena);
}

void ScriptLoader::CalcArenaData(ArenaLayoutData& arena)
{
        std::cout << "Calculating Arena Data from Loaded Script\n";

        arena.TopWallSize = {SCREEN_WIDTH-70, arena.WALL_THICKNESS};
        arena.BottomWallSize = {SCREEN_WIDTH-70, arena.WALL_THICKNESS};
        arena.LeftWallSize = {arena.WALL_THICKNESS, SCREEN_HEIGHT-arena.WALL_BUFFER};
        arena.RightWallSize = {arena.WALL_THICKNESS, SCREEN_HEIGHT-arena.WALL_BUFFER};

        arena.WallSizes = {arena.TopWallSize, arena.BottomWallSize, arena.LeftWallSize, arena.RightWallSize};

        arena.GoalTopWallSize = { arena.GoalSize.x + (2 * arena.WALL_THICKNESS), arena.WALL_THICKNESS };
        arena.GoalBotWallSize = { arena.GoalSize.x + (2 * arena.WALL_THICKNESS), arena.WALL_THICKNESS };
        arena.GoalSideWallSize = { arena.WALL_THICKNESS, arena.GoalSize.y };
        arena.GoalWallSizes = { arena.GoalTopWallSize, arena.GoalBotWallSize, arena.GoalSideWallSize };

        arena.Goal1TopWallPos = { arena.GoalPositions[0].x, arena.GoalPositions[0].y - arena.GoalSize.y/2 };
        arena.Goal1BotWallPos = { arena.GoalPositions[0].x, arena.GoalPositions[0].y + arena.GoalSize.y/2 };
        arena.Goal1SideWallPos = { arena.GoalPositions[0].x + arena.GoalSize.x/2, arena.GoalPositions[0].y };
        arena.Goal1WallPositions = {arena.Goal1TopWallPos, arena.Goal1BotWallPos, arena.Goal1SideWallPos};
        
        arena.Goal2TopWallPos = { arena.GoalPositions[1].x, arena.GoalPositions[1].y - arena.GoalSize.y/2 };
        arena.Goal2BotWallPos = { arena.GoalPositions[1].x, arena.GoalPositions[1].y + arena.GoalSize.y/2 };

        arena.Goal2SideWallPos = { arena.GoalPositions[1].x - arena.GoalSize.x/2, arena.GoalPositions[1].y };
        arena.Goal2WallPositions = { arena.Goal2TopWallPos, arena.Goal2BotWallPos, arena.Goal2SideWallPos };
        arena.StartingPositions = {arena.P1StartingPositions, arena.P2StartingPositions};
}

void ScriptLoader::LoadSingleColor(SDL_Color& color, const std::vector<int>& cvec)
{
    std::cout << "[C++] LoadSingleColor Called.\n";
    
    color.r = static_cast<int>(cvec[0]);
    color.g = static_cast<int>(cvec[1]);
    color.b = static_cast<int>(cvec[2]);
    color.a = static_cast<int>(cvec[3]);

    std::cout << "[C++] LoadSingleColor Ended.\n";
}

void ScriptLoader::LoadPlayerSelectorColors(const char* color_data_script, PlayerColorData& color_data)
{
    std::cout << "Loading colors from: " << color_data_script << " \n";

    sol::state lua{};
    lua.open_libraries(sol::lib::base);
    lua.script_file(color_data_script);

    sol::function luaColorLoader = lua["ColorLoad"];
    std::vector<int> tempColor;
    tempColor.reserve(4);

    sol::tie( tempColor[0], tempColor[1], tempColor[2], tempColor[3] ) = luaColorLoader(1);
    LoadSingleColor(color_data.p1_sel_color, tempColor);

    sol::tie( tempColor[0], tempColor[1], tempColor[2], tempColor[3] ) = luaColorLoader(2);
    LoadSingleColor(color_data.p2_sel_color, tempColor);

    std::cout << "Player Colors Loaded Successfully.\n";
}
