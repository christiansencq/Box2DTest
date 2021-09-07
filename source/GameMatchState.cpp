#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer, ScriptLoader& script_loader)
 : m_Renderer(renderer), m_ScriptLoader(script_loader), m_EntityManager(EntityManager()), 
    m_AssetManager(AssetManager{m_Renderer}), m_PhysicsWorld(InitPhysics()), 
    m_ObjectFactory(ObjectFactory{m_Renderer, m_AssetManager, m_EntityManager, m_PhysicsWorld}), 
    m_PlayerManager{m_ObjectFactory, arena, keybindData},
    m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0)
{
    std::cout << "Loading script\n";
    m_ScriptLoader.SolLoadArenaData("lHockey.lua", arena);
    m_ScriptLoader.LoadPlayerSelectorColors("lColors.lua", color);
    m_ScriptLoader.LoadKeybinds("lKeys.lua", keybindData);
    
    std::cout <<"Setup Fonts.\n";
    m_AssetManager.AddFont("ScoreFont", "arial.ttf", 10);

    std::cout << "Initializing PlayerManager\n";

    //Load Player Colors.
    //Factor this out. I dont like the indirection where PlayerManager is also calling ObjectFactory.
    std::cout << "Setting Up Objects.\n";
    //Pass in keybindings here instead of in constructor?
    m_PlayerManager.SetUpPlayers(color, NumPlayers);

    std::cout << "Creating puck\n";
    m_ObjectFactory.CreatePuck(arena.PuckPosition);

    std::cout << "Creating walls\n";
    m_ObjectFactory.CreateOuterWalls(arena.WallPositions, arena.WallSizes);
    m_ObjectFactory.CreateGoalWalls(arena.Goal1WallPositions, arena.GoalWallSizes);
    m_ObjectFactory.CreateGoalWalls(arena.Goal2WallPositions, arena.GoalWallSizes);
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
                // case SDLK_RETURN:
                //      App::Singleton().PushState(PauseState);
                case SDLK_SPACE:
                    break;
                default:
                    m_PlayerManager.HandleKeyPresses(event.key.keysym.sym);
                    break;
            }
            break;
        }

        case SDL_KEYUP:
        {
            m_PlayerManager.HandleKeyReleases(event.key.keysym.sym);
            break;
        }

        default:
            m_EntityManager.HandleInput(event);
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
    //GameEntityManager
    m_EntityManager.Update();
}

void GameMatchState::Render(SDL_Renderer* renderer)
{
    //Render Background
    SDL_SetRenderDrawColor(renderer, 0x44, 0x99, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Render the images of the Entities    
    if (!m_EntityManager.HasEntities())
    {
        std::cout << "There are no entities!";
        return;
    }
    else
    {
        m_EntityManager.Render(renderer);
    }
    
    SDL_RenderPresent(renderer);
}


//Private Methods
b2World* GameMatchState::InitPhysics()
{
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    b2World* PhysicsWorld = new b2World(gravity);
    return PhysicsWorld;
}

