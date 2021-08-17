#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer)
 : m_Renderer(renderer), m_EntityManager(std::make_shared<EntityManager>()), m_AssetManager(std::make_shared<AssetManager>()), m_ScriptLoader(std::make_shared<ScriptLoader>()),
    m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0) 
{
    std::cout << "Loading script\n";
    m_ScriptLoader->LoadArenaData("lHockey.lua", arena);
    std::cout << "Done loading script\n";

    //Not initializing in init list because we need to load a script first.  Possibly refactor.
    InitPhysics();

    // LoadArenaData(std::string("lHockey.lua"));
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);

    //Set Up Managers and Physics.
    std::cout << "Initializing EntityFactory.\n";
    m_EntityFactory = std::make_unique<EntityFactory>(m_Renderer, m_AssetManager, m_EntityManager, m_PhysicsWorld);

    std::cout << "Setting Up Players.\n";
    SetUpTwoPlayers();

    std::cout << "Setting up Arena.\n";
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
        std::cout << "Creating a player\n";
        std::shared_ptr<Player> player = std::make_shared<Player>(keybindData.SwapKeys[i], keybindData.ActionKeys[i]);

        player->id_number = i;
        std::cout << "Player number : " << player->id_number << "\n";

        std::cout << "setting Starting positions\n";
        std::cout << "Arena.StartingPositions[i] : " << arena.StartingPositions[i][0].x << "  " << arena.StartingPositions[i][0].y << "\n";
        player->AddStartingPositions(arena.StartingPositions[i]);

        std::cout << "Adding Player balls.\n";
        AddPlayerBalls(player, TeamSize);

        m_EntityFactory->CreateScoreDisplay(player, arena.ScoreDisplayPositions[i], arena.GoalSize);
        m_EntityFactory->CreateGoalZone(player, arena.GoalPositions[i], arena.GoalSize);

        player->SwapActiveBall(0);
        
        m_EntityManager->AddPlayer(player);
        m_Players.push_back((player));
    }
}


void GameMatchState::AddPlayerBalls(std::shared_ptr<Player> player, int team_size)
{
    for (int i = 0; i < team_size; i++)
    {
        m_EntityFactory->CreatePlayerBall(player, arena.StartingPositions[player->id_number][i]);
    }
}
