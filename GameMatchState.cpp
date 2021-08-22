#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer, std::shared_ptr<ScriptLoader> script_loader)
 : m_Renderer(renderer), m_ScriptLoader(script_loader), m_EntityManager(std::make_shared<EntityManager>()), m_AssetManager(std::make_shared<AssetManager>()),
    m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0) 
{

    std::cout << "Loading script\n";
    m_ScriptLoader->LoadArenaData("lHockey.lua", arena);
    std::cout << "Done loading script\n";

    std::cout << "Initializing Physics.\n";
    InitPhysics();
    
    std::cout <<"Setup Fonts.\n";
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);

    //Finish Setting Up Managers that require Data/Libraries to be set up.
    std::cout << "Initializing ObjectFactory.\n";
    m_ObjectFactory = std::make_unique<ObjectFactory>(m_Renderer, arena, m_AssetManager, m_EntityManager, m_PhysicsWorld);

    std::cout << "Initializing PlayerManager\n";
    m_PlayerManager = std::make_shared<PlayerManager>(m_ObjectFactory, arena);


    //Set Up Using the Managers.

    std::cout << "Setting Up Players.\n";
    m_PlayerManager->SetUpPlayers(NumPlayers);

    std::cout << "Setting up Arena.\n";
    m_ObjectFactory->CreatePuck({SCREEN_WIDTH/2, SCREEN_HEIGHT/2});

    m_ObjectFactory->CreateOuterWalls(arena.WallPositions, arena.WallSizes);
    m_ObjectFactory->CreateGoalWalls(arena.Goal1WallPositions, arena.GoalWallSizes);
    m_ObjectFactory->CreateGoalWalls(arena.Goal2WallPositions, arena.GoalWallSizes);
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
                    m_PlayerManager->HandleKeyPresses(event.key.keysym.sym);
                    break;
            }
            break;
        }

        case SDL_KEYUP:
        {
            m_PlayerManager->HandleKeyReleases(event.key.keysym.sym);
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



//Private Methods

void GameMatchState::InitPhysics()
{
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    m_PhysicsWorld = new b2World(gravity);
    // m_CollisionManager = new CollisionManager();
    // m_PhysicsWorld->SetContactListener(m_CollisionManager);
}
