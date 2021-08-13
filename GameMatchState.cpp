#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer)
 : m_Renderer(renderer), m_EntityManager(std::make_shared<EntityManager>()), m_AssetManager(std::make_shared<AssetManager>()),
    m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0) 
{

    InitPhysics();

    LoadArenaData(std::string("lHockey.lua"));
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);

    //Set Up Managers and Physics.

    m_EntityFactory = std::make_unique<EntityFactory>(m_Renderer, m_EntityManager, m_PhysicsWorld);


    SetUpTwoPlayers();

    m_EntityFactory->CreatePuck({SCREEN_WIDTH/2, SCREEN_HEIGHT/2});

    m_EntityFactory->CreateOuterWalls(arena.WallPositions, arena.WallSizes);

    //CreateBoundaries();

    CreateGoalWalls();
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

        player->AddStartingPositions(arena.StartingPositions[i]);

        std::cout << "Setting up player's ball \n";
        //Set Up the balls that each player will control.
        for (int j = 0; j < TeamSize; j++)
        {
            AddPlayerBall(player, i, j);
        }


        //player->SwapActiveBall(0);
        std::cout << "Setting Up player's score display \n";

        //Set up the score display
        Entity* score_display = m_EntityManager->AddEntity(arena.ScoreDisplayPositions[i], b2Vec2{50, 20});
        score_display->AddComponent<TextComponent>(m_AssetManager, m_Renderer, std::string(std::to_string(i) + " Score"), "ScoreFont");
        player->AddScoreDisplay(score_display);

        std::cout << "Setting Up player's goal zone. \n";
        //Set up the Goal Zone
        Entity* goal_zone = m_EntityManager->AddEntity(arena.GoalPositions[i], arena.GoalSize);
        goal_zone->AddComponent<GoalZoneComponent>(m_PhysicsWorld, player);

        
        std::cout << "Set Players ActiveBall  \n";

        //Finally:
        player->SwapActiveBall(0);
        
        std::cout << "Add Player to EntityManager  \n";
        m_EntityManager->AddPlayer(player);
        m_Players.push_back((player));
        
    }
}

void GameMatchState::SetUpPuck()
{
    Entity* puck = m_EntityManager->AddEntity(puckStart, 25.0f);
    puck->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody); 
    puck->GetComponent<PhysicsComponent>()->SetData(true);
    puck->AddComponent<SDLCircleComponent>(m_Renderer, GREEN);
}

void GameMatchState::AddPlayerBall(std::shared_ptr<Player> player, int i, int j)
{
    std::cout << "Position of Ball " << arena.StartingPositions[i][j].x << " , " << arena.StartingPositions[i][j].y << ". \n";
    Entity* ball = m_EntityManager->AddEntity(arena.StartingPositions[i][j], 50.0f);
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

void GameMatchState::CreateBoundaries()
{
    // for (int i = 0; i < 4; i++)
    {
    m_EntityFactory->CreateOuterWalls(arena.WallPositions, arena.WallSizes);
    }
}

void GameMatchState::CreateGoalWalls()
{
    m_EntityFactory->CreateGoalWalls(arena.Goal1WallPositions, arena.GoalWallSizes);
    m_EntityFactory->CreateGoalWalls(arena.Goal2WallPositions, arena.GoalWallSizes);

        // Entity* GoalWall = m_EntityManager->AddEntity(arena.Goal1WallPositions[i], arena.GoalWallSizes[i]);
        // GoalWall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
        // GoalWall->GetComponent<PhysicsComponent>()->SetData();
        // GoalWall->AddComponent<SDLRectComponent>(m_Renderer);
    // }
    // for (int i = 0; i < 3; i++)
    // {
    //     m_EntityFactory->CreateGoalWalls(arena.Goal1WallPositions, arena.GoalWallSizes);
    //     Entity* GoalWall = m_EntityManager->AddEntity(arena.Goal2WallPositions[i], arena.GoalWallSizes[i]);
    //     GoalWall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
    //     GoalWall->GetComponent<PhysicsComponent>()->SetData();
    //     GoalWall->AddComponent<SDLRectComponent>(m_Renderer);
    // }
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
            lua_pushstring(L, "WallThickness");
            lua_gettable(L, -2);
            arena.WALL_THICKNESS = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "WallBuffer");
            lua_gettable(L, -2);
            arena.WALL_BUFFER = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "GoalWidth");
            lua_gettable(L, -2);
            arena.GOAL_WIDTH = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "GoalHeight");
            lua_gettable(L, -2);
            arena.GOAL_HEIGHT = lua_tonumber(L, -1);
            lua_pop(L, 1);
        }

        lua_getglobal(L, "P1StartingPos");
        if (lua_istable(L, -1))
        {
            lua_pushstring(L, "x1");
            lua_gettable(L, -2);
            float p1x1 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y1");
            lua_gettable(L, -2);
            float p1y1 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            arena.P1StartingPositions.push_back({p1x1, p1y1});

            std::cout << "P1 b1 " << p1x1 << " , " << p1y1 << "\n";

            lua_pushstring(L, "x2");
            lua_gettable(L, -2);
            float p1x2 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y2");
            lua_gettable(L, -2);
            float p1y2 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            arena.P1StartingPositions.push_back({p1x2, p1y2});

            lua_pushstring(L, "x3");
            lua_gettable(L, -2);
            float p1x3 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y3");
            lua_gettable(L, -2);
            float p1y3 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            arena.P1StartingPositions.push_back({p1x3, p1y3});
        }

        lua_getglobal(L, "P2StartingPos");
        if (lua_istable(L, -1))
        {
            lua_pushstring(L, "x1");
            lua_gettable(L, -2);
            float p2x1 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y1");
            lua_gettable(L, -2);
            float p2y1 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            arena.P2StartingPositions.push_back({p2x1, p2y1});

            lua_pushstring(L, "x2");
            lua_gettable(L, -2);
            float p2x2 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y2");
            lua_gettable(L, -2);
            float p2y2 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            arena.P2StartingPositions.push_back({p2x2, p2y2});

            lua_pushstring(L, "x3");
            lua_gettable(L, -2);
            float p2x3 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y3");
            lua_gettable(L, -2);
            float p2y3 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            arena.P2StartingPositions.push_back({p2x3, p2y3});
        }

        lua_getglobal(L, "ScoreDisplayPos");
        if (lua_istable(L, -1))
        {
            lua_pushstring(L, "x1");
            lua_gettable(L, -2);
            float x1 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y1");
            lua_gettable(L, -2);
            float y1 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            arena.ScoreDisplayPositions.push_back({x1, y1});

            lua_pushstring(L, "x2");
            lua_gettable(L, -2);
            float x2 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "y2");
            lua_gettable(L, -2);
            float y2 = lua_tonumber(L, -1);
            lua_pop(L, 1);

            arena.ScoreDisplayPositions.push_back({x2, y2});
        }

        //Put GoalPositions on the Stack.
        lua_getglobal(L, "GoalPositions");
        //Check to make sure that is a table.
        if (lua_istable(L, -1))
        {

            //Using the Lua stack, Get the two values of P1.
            lua_pushstring(L, "P1");
            //Replace the P1 key with the values at P1.
            lua_gettable(L, -2);
            //Add the index to the stack.
            lua_pushnumber(L, 1);
            //Access the table at -2 (that was given by key 'P1'), at the index at the top of the stack (which is currently 1)
            // Remember, lua tables start from 1, not 0.
            lua_gettable(L, -2);
            float g1x = lua_tonumber(L, -1);

            lua_pop(L, 1);
            lua_pushnumber(L, 2);
            lua_gettable(L, -2);
            float g1y = lua_tonumber(L, -1);
            arena.GoalPositions.push_back({g1x, g1y});

            lua_pop(L, 2);

            lua_pushstring(L, "P2");
            lua_gettable(L, -2); //This push
            lua_pushnumber(L, 1);
            lua_gettable(L, -2);

            float g2x = lua_tonumber(L, -1);
            lua_pop(L, 1);

            lua_pushnumber(L, 2);
            lua_gettable(L, -2);
            float g2y = lua_tonumber(L, -1);

            arena.GoalPositions.push_back({g2x, g2y});

            std::cout << "G2x, y " << g2x << "   " << g2y << "\n";
        }

//Dependent Variables
        arena.StartingPositions = {arena.P1StartingPositions, arena.P2StartingPositions};

            //Set the variables dependent on those pulled from lua.
        arena.GoalSize.x = arena.GOAL_WIDTH;
        arena.GoalSize.y = arena.GOAL_HEIGHT;

        arena.TopWallSize = {SCREEN_WIDTH-70, arena.WALL_THICKNESS};
        arena.BottomWallSize = {SCREEN_WIDTH-70, arena.WALL_THICKNESS};
        arena.LeftWallSize = {arena.WALL_THICKNESS, SCREEN_HEIGHT-arena.WALL_BUFFER};
        arena.RightWallSize = {arena.WALL_THICKNESS, SCREEN_HEIGHT-arena.WALL_BUFFER};
        arena.WallSizes = {arena.TopWallSize, arena.BottomWallSize, arena.LeftWallSize, arena.RightWallSize};

        arena.GoalTopWallSize = { arena.GOAL_WIDTH + (2 * arena.WALL_THICKNESS), arena.WALL_THICKNESS };
        arena.GoalBotWallSize = { arena.GOAL_WIDTH + (2 * arena.WALL_THICKNESS), arena.WALL_THICKNESS };
        arena.GoalSideWallSize = { arena.WALL_THICKNESS, arena.GOAL_HEIGHT };
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
