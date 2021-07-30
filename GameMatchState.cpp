#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer)
 : m_Renderer(renderer), m_EntityManager(std::make_unique<EntityManager>()), m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0) 
 {
//    m_EntityManager = std::make_unique<EntityManager>();
    m_AssetManager = new AssetManager();
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);

    //Set Up Managers and Physics.
    InitPhysics();

    //Player Setup
    SetUpTwoPlayers();

    //Arena Setup.
    SetUpPuck();
    CreateBoundaries2();
    CreateGoalWalls();
}

GameMatchState::~GameMatchState()
{
    delete m_PhysicsWorld;
    delete m_AssetManager;
    delete m_CollisionManager;
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
    m_CollisionManager = new CollisionManager();
    m_PhysicsWorld->SetContactListener(m_CollisionManager);
}

void GameMatchState::SetUpTwoPlayers()
{
    //Assert that the Vectors are long enough to supply the keybindings and that there are2 plaeyrs and 3 in Team.
    for (int i = 0; i < NumPlayers; i++)
    {
        //Create a player with some keybindings set-up
        std::shared_ptr<Player> player = std::make_shared<Player>(keybindData.SwapKeys[i], keybindData.ActionKeys[i]);

        player->AddStartingPositions(arenaData.StartingPositions[i]);

        //Set Up the balls that each player will control.
        for (int j = 0; j < TeamSize; j++)
        {
            AddPlayerBall(player, i, j);
        }
        player->SwapActiveBall(0);

        std::cout << "Active Ball (0), has SDLCircle? " << player->GetActive()->HasComponent<SDLCircleComponent>() << "\n";

        std::cout << "Active Ball SDLCircle X, Y " << player->GetActive()->GetComponent<SDLCircleComponent>()->GetX() << ", " << player->GetActive()->GetComponent<SDLCircleComponent>()->GetY()  << "\n";


        //Set up the score display
        Entity* score_display = m_EntityManager->AddEntity(arenaData.ScoreDisplayPositions[i], b2Vec2{50, 20});
        score_display ->AddComponent<TextComponent>(m_AssetManager, m_Renderer, std::string(std::to_string(i) + " Score"), "ScoreFont");
        player->AddScoreDisplay(score_display);

        //Set up the Goal Zone
        Entity* goal_zone = m_EntityManager->AddEntity(arenaData.GoalPositions[i], arenaData.GoalSize);
        goal_zone->AddComponent<GoalZoneComponent>(m_PhysicsWorld, player);
        goal_zone->GetComponent<GoalZoneComponent>()->SetData(false);

        //Finally:
//        player->SwapActiveBall(0);
        m_EntityManager->AddPlayer(player);
        m_Players.push_back((player));
    }
}

void GameMatchState::SetUpPuck()
{ Entity* puck = m_EntityManager->AddEntity(puckStart, 25.0f);
    puck->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody); 
    puck->GetComponent<PhysicsComponent>()->SetData(true);
    puck->AddComponent<SDLCircleComponent>(m_Renderer, GREEN);
}

void GameMatchState::AddPlayerBall(std::shared_ptr<Player> player, int i, int j)
{
    Entity* ball = m_EntityManager->AddEntity(arenaData.StartingPositions[i][j], 50.0f);
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

void GameMatchState::CreateBoundaries2()
{
    for (int i = 0; i < 4; i++)
    {
    Entity* wall = m_EntityManager->AddEntity(arenaData.WallPoses[i], arenaData.WallSizes[i]);
    wall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
    wall->GetComponent<PhysicsComponent>()->SetData();
    wall->AddComponent<SDLRectComponent>(m_Renderer);
    }
}

void GameMatchState::CreateGoalWalls()
{
    for (int i = 0; i < 3; i++)
    {
        Entity* GoalWall = m_EntityManager->AddEntity(arenaData.Goal1WallPositions[i], arenaData.GoalWallSizes[i]);
        GoalWall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
        GoalWall->GetComponent<PhysicsComponent>()->SetData();
        GoalWall->AddComponent<SDLRectComponent>(m_Renderer);
    }
    for (int i = 0; i < 3; i++)
    {
        Entity* GoalWall = m_EntityManager->AddEntity(arenaData.Goal2WallPositions[i], arenaData.GoalWallSizes[i]);
        GoalWall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
        GoalWall->GetComponent<PhysicsComponent>()->SetData();
        GoalWall->AddComponent<SDLRectComponent>(m_Renderer);
    }
}
