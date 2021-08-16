#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer)
 : m_Renderer(renderer), m_EntityManager(std::make_shared<EntityManager>()), m_AssetManager(std::make_shared<AssetManager>()),
    m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0) 
{

    InitPhysics();

    LoadArenaData(std::string("lHockey.lua"));
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);

    //Set Up Managers and Physics.

    m_EntityFactory = std::make_unique<EntityFactory>(m_Renderer, m_AssetManager, m_EntityManager, m_PhysicsWorld);

    SetUpTwoPlayers();

    m_EntityFactory->CreatePuck({SCREEN_WIDTH/2, SCREEN_HEIGHT/2});

    m_EntityFactory->CreateOuterWalls(arena.WallPositions, arena.WallSizes);

    m_EntityFactory->CreateGoalWalls(arena.Goal1WallPositions, arena.GoalWallSizes);
    m_EntityFactory->CreateGoalWalls(arena.Goal2WallPositions, arena.GoalWallSizes);
}

GameMatchState::~GameMatchState()
{
    delete m_PhysicsWorld;
    //delete m_CollisionManager;
}

void GameMatchState::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            App::Singleton().QuitApp();
            break;
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    App::Singleton().QuitApp();
                    break;
                case SDLK_SPACE:
                    break;
                default:
                    m_EntityManager->HandleKeyPresses(event.key.keysym.sym);
                    break;
            }
            break;
        }

        case SDL_KEYUP:
        {
            m_EntityManager->HandleKeyReleases(event.key.keysym.sym);
            break;
        }

        default:
            m_EntityManager->HandleInput(event);
    }
}

void GameMatchState::Update()
{
    unsigned int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - m_TicksLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) 
    {
        SDL_Delay(timeToWait);
    }
    //float deltaTime = (SDL_GetTicks() - m_TicksLastFrame) / 1000.0f;
    //deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    m_TicksLastFrame = SDL_GetTicks();
    m_PhysicsWorld->Step(m_TimeStep, m_VelocityIterations, m_PositionIterations); 
    m_EntityManager->Update();
}

void GameMatchState::Render(SDL_Renderer* renderer)
{
    //Render Background
    SDL_SetRenderDrawColor(renderer, 0x44, 0x99, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Render the images of the Entities    
    if (!m_EntityManager->HasEntities())
    {
        std::cout << "There are no entities!";
        return;
    }
    else
    {
        m_EntityManager->Render(renderer);
    }
    
    SDL_RenderPresent(renderer);
}


//SET UP Private Methods

//Much below this can be replaced by data/scripting.
void GameMatchState::InitPhysics()
{
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    m_PhysicsWorld = new b2World(gravity);
    // m_CollisionManager = new CollisionManager();
    // m_PhysicsWorld->SetContactListener(m_CollisionManager);
}

void GameMatchState::SetUpTwoPlayers()
{
    assert((NumPlayers != static_cast<int>(keybindData.SwapKeys.size())) && "Num of Swap keybinds != NumPlayers");
    assert((NumPlayers != static_cast<int>(keybindData.ActionKeys.size())) && "Num of Action keybind != Num Players");

    for (int i = 0; i < NumPlayers; i++)
    {
        std::shared_ptr<Player> player = std::make_shared<Player>(keybindData.SwapKeys[i], keybindData.ActionKeys[i]);

        player->id_number = i;
        player->AddStartingPositions(arena.StartingPositions[i]);

        AddPlayerBalls(player, TeamSize);

        m_EntityFactory->CreateScoreDisplay(player, arena.ScoreDisplayPositions[i], arena.GoalSize);
        m_EntityFactory->CreateGoalZone(player, arena.ScoreDisplayPositions[i], arena.GoalSize);

        player->SwapActiveBall(0);
        
        m_EntityManager->AddPlayer(player);
        m_Players.push_back((player));
    }
}


void GameMatchState::AddPlayerBalls(std::shared_ptr<Player> player, int team_size)
{
    for (int i = 0; i < team_size; i++)
    {
        Entity* ball = m_EntityManager->AddEntity(arena.StartingPositions[player->id_number][i], 50.0f);
        player->AddBallToTeam(ball);
        ball->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody);
        ball->GetComponent<PhysicsComponent>()->SetData();
        ball->AddComponent<SDLCircleComponent>(m_Renderer);
        ball->AddComponent<SelectableComponent>(m_Renderer);
        ball->AddComponent<KeyInputComponent>(player->GetActionKeys());
        ball->GetComponent<KeyInputComponent>()->AddCommand<ForwardThrustCommand>();
        ball->GetComponent<KeyInputComponent>()->AddCommand<BackwardThrustCommand>();
        ball->GetComponent<KeyInputComponent>()->AddCommand<LeftTurnCommand>();
        ball->GetComponent<KeyInputComponent>()->AddCommand<RightTurnCommand>();
    }
}

bool GameMatchState::CheckLua(lua_State* L, int r)
{
    if (r != LUA_OK)
    {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}

void GameMatchState::LuaGetTableFromKey(lua_State* L, const char* key)
{
    lua_pushstring(L, key);
    lua_gettable(L, -2);
}

float GameMatchState::LuaIndexToFloat(lua_State* L, int index)
{
    float num;

    lua_pushnumber(L, index);
    lua_gettable(L, -2);
    num = lua_tonumber(L, -1);
    lua_pop(L, 1);

    return num;
}

float GameMatchState::LuaKeyToFloat(lua_State* L, const char* lua_var_name)
{
    float num;
    lua_pushstring(L, lua_var_name);
    lua_gettable(L, -2);
    num = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return num;
}

b2Vec2 GameMatchState::LuaKeyTob2Vec(lua_State* L, const char* key)
{
    b2Vec2 point;
    LuaGetTableFromKey(L, key);

    point.x = LuaIndexToFloat(L, 1);
    point.y = LuaIndexToFloat(L, 2);
 
    lua_pop(L, 1);

    return point;
}

bool GameMatchState::LoadArenaData(std::string arena_data_file)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if(CheckLua(L, luaL_dofile(L, arena_data_file.c_str())))
    {
        lua_getglobal(L, "lua_arena");
        std::cout << "Loading variables from lua_arena \n";
        if (lua_istable(L, -1))
        {
            arena.WALL_THICKNESS = LuaKeyToFloat(L, "WallThickness");
            arena.WALL_BUFFER = LuaKeyToFloat(L, "WallBuffer");
        }

        lua_getglobal(L, "GoalSize");
        if (lua_istable(L, -1))
        {
            arena.GoalSize.x = LuaIndexToFloat(L, 1); 
            arena.GoalSize.y = LuaIndexToFloat(L, 2); 
        }

        lua_getglobal(L, "BallStartPos");
        if (lua_istable(L, -1))
        {
            LuaGetTableFromKey(L, "P1");
            b2Vec2 P1b1 = LuaKeyTob2Vec(L, "b1");
            b2Vec2 P1b2 = LuaKeyTob2Vec(L, "b2");
            b2Vec2 P1b3 = LuaKeyTob2Vec(L, "b3");

            arena.P1StartingPositions = { P1b1, P1b2, P1b3 };

            lua_pop(L, 1);

            LuaGetTableFromKey(L, "P2");
            b2Vec2 P2b1 = LuaKeyTob2Vec(L, "b1");
            b2Vec2 P2b2 = LuaKeyTob2Vec(L, "b2");
            b2Vec2 P2b3 = LuaKeyTob2Vec(L, "b3");

            arena.P2StartingPositions  = { P2b1, P2b2, P2b3 };
        }

        lua_getglobal(L, "ScoreDisplayPos");
        if (lua_istable(L, -1))
        {
            b2Vec2 P1vec = LuaKeyTob2Vec(L, "P1");
            b2Vec2 P2vec = LuaKeyTob2Vec(L, "P2");

            arena.ScoreDisplayPositions.push_back(P1vec);
            arena.ScoreDisplayPositions.push_back(P2vec);
        }

        lua_getglobal(L, "GoalPositions");
        if (lua_istable(L, -1))
        {
            b2Vec2 P1GoalPos = LuaKeyTob2Vec(L, "P1");
            b2Vec2 P2GoalPos = LuaKeyTob2Vec(L, "P2");
            arena.GoalPositions.push_back(P1GoalPos);
            arena.GoalPositions.push_back(P2GoalPos);
        }

        //Dependent Variables
        arena.StartingPositions = {arena.P1StartingPositions, arena.P2StartingPositions};

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
    
        lua_close(L);
        return true;
    }
    else
    {
        return false;
    }
}
