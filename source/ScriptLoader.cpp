#include "ScriptLoader.h"
#include "Data/Constants.h"

ScriptLoader::ScriptLoader()
{
}

ScriptLoader::~ScriptLoader()
{
}

void ScriptLoader::SolLoadArenaData(std::string arena_data_file, ArenaLayoutData& arena)
{
    sol::state lua{};
    lua.open_libraries(sol::lib::base); 
    
    lua.set("SCREEN_WIDTH", SMALL_SCREEN_W);
    lua.set("SCREEN_HEIGHT", SMALL_SCREEN_H);

    lua.script_file(arena_data_file.c_str());

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

    arena.PuckPosition = { lua["PuckPos"][1], lua["PuckPos"][2] };

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
    
    arena.TopWallPos = { lua["TopWallPos"][1], lua["TopWallPos"][2] };
    arena.BottomWallPos = { lua["BottomWallPos"][1], lua["BottomWallPos"][2] };
    arena.LeftWallPos = { lua["LeftWallPos"][1], lua["LeftWallPos"][2] };
    arena.RightWallPos = { lua["RightWallPos"][1], lua["RightWallPos"][2] };

    arena.WallPositions = {arena.TopWallPos, arena.BottomWallPos, arena.LeftWallPos, arena.RightWallPos };

    CalcArenaData(arena);
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

    //Can loop this for the number of players.
    sol::tie( tempColor[0], tempColor[1], tempColor[2], tempColor[3] ) = luaColorLoader(1);
    LoadSingleColor(color_data.p1_sel_color, tempColor);

    sol::tie( tempColor[0], tempColor[1], tempColor[2], tempColor[3] ) = luaColorLoader(2);
    LoadSingleColor(color_data.p2_sel_color, tempColor);

    std::cout << "[C++] Player Colors Loaded Successfully.\n";
}


void ScriptLoader::LoadKeybinds(const char* keybind_data_file, KeyBindingData& keybind)
{
    std::cout << "[C++] Loading keybinds from: " << keybind_data_file << " \n";
    sol::state lua{};

    lua.open_libraries(sol::lib::base);

    lua["SDLK"] = lua.create_table_with (
            "a", SDLK_a, "b", SDLK_b, "c", SDLK_c,
            "d", SDLK_d, "e", SDLK_e, "f", SDLK_f,
            "g", SDLK_g, "h", SDLK_h, "i", SDLK_i,
            "j", SDLK_j, "k", SDLK_k, "l", SDLK_l,
            "m", SDLK_m, "n", SDLK_n, "o", SDLK_o,
            "p", SDLK_p, "q", SDLK_q, "r", SDLK_r,
            "s", SDLK_s, "t", SDLK_t, "u", SDLK_u,
            "v", SDLK_v, "w", SDLK_w, "x", SDLK_x,
            "y", SDLK_y, "z", SDLK_z,
            "0", SDLK_0, "1", SDLK_1, "2", SDLK_2, "3", SDLK_3, "4", SDLK_4, 
            "5", SDLK_5, "6", SDLK_6, "7", SDLK_7, "8", SDLK_8, "9", SDLK_9,
            "UP", SDLK_UP, "DOWN", SDLK_DOWN, "LEFT", SDLK_LEFT, "RIGHT", SDLK_RIGHT
            );

    lua.script_file(keybind_data_file);

    //TODO insert a check to make sure the keys are valid to be assigned to a player.

    std::vector<SDL_Keycode> p1tempswap;
    std::vector<SDL_Keycode> p2tempswap;
    std::vector<SDL_Keycode> p1tempdir;
    std::vector<SDL_Keycode> p2tempdir;

    p1tempswap = { static_cast<SDL_Keycode>(lua["SwapKeys"]["P1"][1]), 
                   static_cast<SDL_Keycode>(lua["SwapKeys"]["P1"][2]),
                   static_cast<SDL_Keycode>(lua["SwapKeys"]["P1"][3])};

    // keybind.P1SwapKeys = { static_cast<SDL_Keycode>(lua["SwapKeys"]["P1"][1]), 
    //                        static_cast<SDL_Keycode>(lua["SwapKeys"]["P1"][2]),
    //                        static_cast<SDL_Keycode>(lua["SwapKeys"]["P1"][3])};
    //

    p2tempswap = { static_cast<SDL_Keycode>(lua["SwapKeys"]["P2"][1]),
                   static_cast<SDL_Keycode>(lua["SwapKeys"]["P2"][2]),
                   static_cast<SDL_Keycode>(lua["SwapKeys"]["P2"][3])};

    // keybind.P2SwapKeys = { static_cast<SDL_Keycode>(lua["SwapKeys"]["P2"][1]),
    //                        static_cast<SDL_Keycode>(lua["SwapKeys"]["P2"][2]),
    //                        static_cast<SDL_Keycode>(lua["SwapKeys"]["P2"][3])};

    p1tempdir = { static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][1]),
                  static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][2]),
                  static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][3]),
                  static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][4]) };

    // keybind.P1DirectionKeys = { static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][1]),
    //                             static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][2]),
    //                             static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][3]),
    //                             static_cast<SDL_Keycode>(lua["DirectionKeys"]["P1"][4]) };

    p2tempdir = { static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][1]),
                  static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][2]),
                  static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][3]),
                  static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][4]) };

    // keybind.P2DirectionKeys = { static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][1]),
    //                             static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][2]),
    //                             static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][3]),
    //                             static_cast<SDL_Keycode>(lua["DirectionKeys"]["P2"][4]) };

    // keybind.P1Keys = { keybind.P1SwapKeys, keybind.P1DirectionKeys };
    // keybind.P2Keys = { keybind.P2SwapKeys, keybind.P2DirectionKeys };
    keybind.P1Keys = { p1tempswap, p1tempdir };
    keybind.P2Keys = { p2tempswap, p2tempdir };

    keybind.Keys = { keybind.P1Keys, keybind.P2Keys };

    // std::cout << "keybind P1SwapKeys " << keybind.P1SwapKeys[0] << "  " << keybind.P1SwapKeys[1] << "  " << keybind.P1SwapKeys[2] << " \n\n";
    // std::cout << "keybind P2SwapKeys " << keybind.P2SwapKeys[0] << "  " << keybind.P2SwapKeys[1] << "  " << keybind.P2SwapKeys[2] << " \n\n";

    std::cout << "[C++] Keybinds loaded.\n";
}

//Private
void ScriptLoader::LoadSingleColor(SDL_Color& color, const std::vector<int>& cvec)
{
    std::cout << "[C++] LoadSingleColor Called.\n";
    color.r = static_cast<int>(cvec[0]);
    color.g = static_cast<int>(cvec[1]);
    color.b = static_cast<int>(cvec[2]);
    color.a = static_cast<int>(cvec[3]);
    std::cout << "[C++] LoadSingleColor Ended.\n";
}

void ScriptLoader::CalcArenaData(ArenaLayoutData& arena)
{
        std::cout << "Calculating Arena Data from Loaded Script\n";
        arena.TopWallSize = {SMALL_SCREEN_W-14, arena.WALL_THICKNESS};
        arena.BottomWallSize = {SMALL_SCREEN_W-14, arena.WALL_THICKNESS};
        arena.LeftWallSize = {arena.WALL_THICKNESS, SMALL_SCREEN_H-arena.WALL_BUFFER};
        arena.RightWallSize = {arena.WALL_THICKNESS, SMALL_SCREEN_H-arena.WALL_BUFFER};

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
