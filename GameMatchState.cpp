#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer)
 : m_Renderer(renderer), m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0)
 {
    //SETUP FONT
    m_ScoreFont = TTF_OpenFont("arial.ttf", 14);
    !m_ScoreFont ? std::cout << "Failed to load font! \n" : std::cout << "Font loaded fine. \n";

    //SETUP ARENA START
    InitWorld();


    puckObj = m_EntityManager->AddEntity(puckStart, 25.0f);
    puckObj->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody); 
    puckObj->GetComponent<PhysicsComponent>()->SetData(true);
    //puckObj->GetComponent<PhysicsComponent>()->SetCollisionCategory(PUCK_BITS);
    puckObj->AddComponent<SDLCircleComponent>(m_Renderer, GREEN);
    CreateBoundaries();
    //SETUP ARENA END

    //SETUP PLAYER CONTROLS START
    m_P1 = std::make_shared<Player>(P1SwapKeys, P1ActionKeys);
    //m_P2 = std::make_shared<Player>(P2SwapKeys, P2ActionKeys);

    //SETUP PLAYER CONTROLS END

    //Set Up the balls that each player will control.
    movingObj1 = m_EntityManager->AddEntity(P1StartingPositions[0], 50.0f);
    AddPlayerBall(movingObj1, m_P1);//This is just a complicated way of assigning a variable should just have Player added to Entity (Could also be a Scorer or a Arena object)
    movingObj2 = m_EntityManager->AddEntity(P1StartingPositions[1], 50.0f);
    AddPlayerBall(movingObj2, m_P1);
    movingObj3 = m_EntityManager->AddEntity(P1StartingPositions[2], 50.0f);
    AddPlayerBall(movingObj3, m_P1);

    //Player Setup
    SetUpPlayers();

    //Goal Setup.
    goalZone = m_EntityManager->AddEntity(b2Vec2{1300, 450}, b2Vec2{250, 500});    
    goalZone->AddComponent<GoalZoneComponent>(m_PhysicsWorld, m_P1);
    goalZone->GetComponent<GoalZoneComponent>()->SetData(false);

    
    //Call Reset - Which will determine the actual position
    
}

GameMatchState::~GameMatchState()
{
    delete m_PhysicsWorld;
    delete m_AssetManager;
    delete m_CollisionManager;
}

//Possibly move this up above the constructor?  Move Functions that are resolved by the end of
// Constructor/ Update/ Render to just before those functions.  <F8>
void GameMatchState::SetUpPlayers()
{
    //Score
    m_P1ScoreDisplayUI = m_EntityManager->AddEntity(ScoreDisplayPositions[0], b2Vec2{50, 20});
    m_P1ScoreDisplayUI->AddComponent<TextComponent>(m_AssetManager, m_Renderer, "P1Score", "ScoreFont");

    m_P1->AddStartingPositions(P1StartingPositions);
    m_P1->AddScoreDisplay(m_P1ScoreDisplayUI);
    m_EntityManager->AddPlayer(m_P1);
    m_Players.push_back((m_P1));

//    m_P2ScoreDisplayUI = m_EntityManager->AddEntity(ScoreDisplayPositions[1], b2Vec2{50, 20});
//    m_P2ScoreDisplayUI->AddComponent<TextComponent>(m_AssetManager, m_Renderer, "P2Score", "ScoreFont");

    //m_EntityManager->AddPlayer(m_P2);
    //m_Players.push_back(m_P2);
}

void GameMatchState::InitPlayers(int num_players)
{

}

void GameMatchState::Reset ()
{
    //To be called after a score.
    //This would reset Positions of Entities.  States, abilities, etc.
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

void GameMatchState::InitWorld()
{
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    m_PhysicsWorld = new b2World(gravity);
    m_EntityManager = std::make_unique<EntityManager>();
    m_AssetManager = new AssetManager{};
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);
    m_CollisionManager = new CollisionManager();
    m_PhysicsWorld->SetContactListener(m_CollisionManager);
}

void GameMatchState::AddPlayerBall(Entity* entity, std::shared_ptr<Player> player)
{
    player->AddBallToTeam(entity);
    entity->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody);
    entity->GetComponent<PhysicsComponent>()->SetData();
    entity->AddComponent<SDLCircleComponent>(m_Renderer, BLUE);
    entity->AddComponent<SelectableComponent>(m_Renderer);
    entity->AddComponent<KeyInputComponent>(player->GetActionKeys());
    entity->GetComponent<KeyInputComponent>()->AddCommand<ForwardThrustCommand>();
    entity->GetComponent<KeyInputComponent>()->AddCommand<BackwardThrustCommand>();
    entity->GetComponent<KeyInputComponent>()->AddCommand<LeftTurnCommand>();
    entity->GetComponent<KeyInputComponent>()->AddCommand<RightTurnCommand>();
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
