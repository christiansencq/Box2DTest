#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer)
 : m_Renderer(renderer), m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0)
 {
    m_EntityManager = std::make_unique<EntityManager>();
    m_AssetManager = new AssetManager();
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);

    //Set Up Managers and Physics.
    InitPhysics();

    //Player Setup
    SetUpPlayers();

    //Arena Setup.
    SetUpPuck();
    CreateBoundaries();
//    CreateGoalZones();
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
                    m_EntityManager->HandleKeyPress(event.key.keysym.sym);
                    break;
            }
            break;
        }

        case SDL_KEYUP:
        {
            m_EntityManager->HandleKeyRelease(event.key.keysym.sym);
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
        //Add stuff to renderer:
        m_EntityManager->Render(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

//Much below this can be replaced by data/scripting.

void GameMatchState::InitPhysics()
{
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    m_PhysicsWorld = new b2World(gravity);
    m_CollisionManager = new CollisionManager();
    m_PhysicsWorld->SetContactListener(m_CollisionManager);
}

//Possibly move this up above the constructor?  Move Functions that are resolved by the end of
// Constructor/ Update/ Render to just before those functions.  <F8>
void GameMatchState::SetUpPlayers()
{
    //m_P1 = std::make_shared<Player>(P1SwapKeys, P1ActionKeys);
    //m_P2 = std::make_shared<Player>(P2SwapKeys, P2ActionKeys);
    std::shared_ptr<Player> player = std::make_shared<Player>(P1SwapKeys, P1ActionKeys);

    //Set Up the balls that each player will control.
    // Each Pulls from the Player's List for its starting position.
    // Eventually add in an argument to add a Ball of a Type/Class etc.
    AddPlayerBall(player);
    AddPlayerBall(player);
    AddPlayerBall(player);

    //Score Object Setup.  Combine this and player->AddScoreDisplay.
    SetUpScoreForPlayer(player);

    //Refactor this so that Player has a static list of starting positions it pulls from?
    player->AddStartingPositions(P1StartingPositions);
    m_EntityManager->AddPlayer(player);
    m_Players.push_back((player));
}

void GameMatchState::SetUpScoreForPlayer(std::shared_ptr<Player> player)
{
    Entity* score_display = m_EntityManager->AddEntity(ScoreDisplayPositions[0], b2Vec2{50, 20});
    score_display ->AddComponent<TextComponent>(m_AssetManager, m_Renderer, "P1Score", "ScoreFont");
    player->AddScoreDisplay(score_display);

    Entity* goal_zone = m_EntityManager->AddEntity(b2Vec2{1300, 450}, b2Vec2{250, 500});    
    goal_zone->AddComponent<GoalZoneComponent>(m_PhysicsWorld, player);
    goal_zone->GetComponent<GoalZoneComponent>()->SetData(false);
}

void GameMatchState::SetUpPuck()
{
    Entity* puck = m_EntityManager->AddEntity(puckStart, 25.0f);
    puck->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody); 
    puck->GetComponent<PhysicsComponent>()->SetData(true);
    //puckObj->GetComponent<PhysicsComponent>()->SetCollisionCategory(PUCK_BITS);
    puck->AddComponent<SDLCircleComponent>(m_Renderer, GREEN);
}

void GameMatchState::AddPlayerBall(std::shared_ptr<Player> player)
{
    //Obviously, refactor so taht the StartingPosition vector is pulled from.
    static std::vector<b2Vec2> TempStartingPos = P1StartingPositions;
    b2Vec2 start_pos = TempStartingPos.back();
    TempStartingPos.pop_back();
    Entity* ball = m_EntityManager->AddEntity(start_pos, 50.0f);
    player->AddBallToTeam(ball);
    ball->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody);
    ball->GetComponent<PhysicsComponent>()->SetData();
    ball->AddComponent<SDLCircleComponent>(m_Renderer, BLUE);
    ball->AddComponent<SelectableComponent>(m_Renderer);
    ball->AddComponent<KeyInputComponent>(player->GetActionKeys());
    ball->GetComponent<KeyInputComponent>()->AddCommand<ForwardThrustCommand>();
    ball->GetComponent<KeyInputComponent>()->AddCommand<BackwardThrustCommand>();
    ball->GetComponent<KeyInputComponent>()->AddCommand<LeftTurnCommand>();
    ball->GetComponent<KeyInputComponent>()->AddCommand<RightTurnCommand>();
}

void GameMatchState::CreateBoundaries()
{
    staticObj1 = m_EntityManager->AddEntity(b2Vec2{SCREEN_WIDTH/2, 30}, b2Vec2{SCREEN_WIDTH-70, WALL_THICKNESS});
    staticObj2 = m_EntityManager->AddEntity(b2Vec2{SCREEN_WIDTH/2, SCREEN_HEIGHT - 30}, b2Vec2{SCREEN_WIDTH-70, WALL_THICKNESS});
    staticObj3 = m_EntityManager->AddEntity(b2Vec2{30, SCREEN_HEIGHT/2}, b2Vec2{WALL_THICKNESS, SCREEN_HEIGHT - WALL_BUFFER});
    staticObj4 = m_EntityManager->AddEntity(b2Vec2{SCREEN_WIDTH-30, SCREEN_HEIGHT/2}, b2Vec2{WALL_THICKNESS, SCREEN_HEIGHT - WALL_BUFFER});
    staticObj1->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
    staticObj1->GetComponent<PhysicsComponent>()->SetData();
    staticObj1->AddComponent<SDLRectComponent>(m_Renderer);
    staticObj2->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
    staticObj2->GetComponent<PhysicsComponent>()->SetData();
    staticObj2->AddComponent<SDLRectComponent>(m_Renderer);
    staticObj3->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
    staticObj3->GetComponent<PhysicsComponent>()->SetData();
    staticObj3->AddComponent<SDLRectComponent>(m_Renderer);
    staticObj4->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
    staticObj4->GetComponent<PhysicsComponent>()->SetData();
    staticObj4->AddComponent<SDLRectComponent>(m_Renderer);
}

