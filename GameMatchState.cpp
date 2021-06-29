#include "GameMatchState.h"

GameMatchState::GameMatchState(SDL_Renderer* renderer)
 : m_Renderer(renderer), m_TimeStep(1/30.0f), m_VelocityIterations(2), m_PositionIterations(6), m_TicksLastFrame(0)
 {
    //SETUP FONT
    m_ScoreFont = TTF_OpenFont("arial.ttf", 14);
    !m_ScoreFont ? std::cout << "Failed to load font! \n" : std::cout << "Font loaded fine. \n";

    //SETUP ARENA START
    InitWorld();

    puckObj = m_Manager->AddEntity(puckStart, 25.0f);
    puckObj->AddComponent<PhysicsComponent>(m_World, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody, isSensor::False);
    puckObj->AddComponent<SDLCircleComponent>(m_Renderer, GREEN);
    CreateBoundaries();
    //SETUP ARENA END

    //SETUP PLAYER CONTROLS START
    m_P1 = std::make_shared<Player>(P1SwapKeys, P1ActionKeys);
    //m_P2 = std::make_shared<Player>(P2SwapKeys, P2ActionKeys);

    //SETUP PLAYER CONTROLS END

    //Set Up the balls that each player will control.
    movingObj1 = m_Manager->AddEntity(P1StartingPositions[0], 50.0f);
    AddPlayerBall(movingObj1, m_P1);//This is just a complicated way of assigning a variable
    movingObj2 = m_Manager->AddEntity(P1StartingPositions[1], 50.0f);
    AddPlayerBall(movingObj2, m_P1);
    movingObj3 = m_Manager->AddEntity(P1StartingPositions[2], 50.0f);
    AddPlayerBall(movingObj3, m_P1);

    //Player Setup
    SetUpPlayers();

    //Goal Setup.
    goalZone = m_Manager->AddEntity(b2Vec2{1300, 450}, b2Vec2{250, 500});    
    goalZone->AddComponent<GoalZoneComponent>(m_World, m_P1);
    //Call Reset - Which will determine the actual position
    
}

GameMatchState::~GameMatchState()
{
    delete m_World;
}

//Possibly move this up above the constructor?  Move Functions that are resolved by the end of
// Constructor/ Update/ Render to just before those functions.  <F8>
void GameMatchState::SetUpPlayers()
{
    //Score
    m_P1ScoreDisplayUI = m_Manager->AddEntity(ScoreDisplayPositions[0], b2Vec2{50, 20});
    m_P1ScoreDisplayUI->AddComponent<TextComponent>(m_AssetManager, m_Renderer, "P1Score", "ScoreFont");

    m_P1->AddStartingPositions(P1StartingPositions);
    m_P1->AddScoreDisplay(m_P1ScoreDisplayUI);
    m_Manager->AddPlayer(m_P1);
    m_Players.push_back((m_P1));

//    m_P2ScoreDisplayUI = m_Manager->AddEntity(ScoreDisplayPositions[1], b2Vec2{50, 20});
//    m_P2ScoreDisplayUI->AddComponent<TextComponent>(m_AssetManager, m_Renderer, "P2Score", "ScoreFont");

    //m_Manager->AddPlayer(m_P2);
    //m_Players.push_back(m_P2);
}

void GameMatchState::InitPlayers(int num_players)
{
    //Literally just creates some basic players that pull a control Scheme
    //for (int i = 0; i < num_players; i++)
    //{
        // 
    //    std::shared_ptr<Player> pl = std::make_shared<Player>();
    //    m_Manager->AddPlayer();
    //}
}

//void GameMatchState::SetUpPlayers(std::vector<std::vector<Entity*>> PlayerTeams)
//{
//Passing in the vector of Players, which at this point are just Vectors of Entities.
//Divide into Players, Teams. Probably combine with AddPlayerBall?
//}

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
                    m_Manager->HandleKeyPress(event.key.keysym.sym);
                    break;
            }
            break;
        }

        case SDL_KEYUP:
        {
            m_Manager->HandleKeyRelease(event.key.keysym.sym);
            break;
        }

        default:
            m_Manager->HandleInput(event);
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
    m_World->Step(m_TimeStep, m_VelocityIterations, m_PositionIterations); 
    m_Manager->Update();
}

void GameMatchState::Render(SDL_Renderer* renderer)
{
    //Render Background
    SDL_SetRenderDrawColor(renderer, 0x44, 0x99, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Render the images of the Entities    
    if (!m_Manager->HasEntities())
    {
        std::cout << "There are no entities!";
        return;
    }
    else
    {
        //Add stuff to renderer:
        m_Manager->Render(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

//Much below this can be replaced by data/scripting.

void GameMatchState::InitWorld()
{
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    m_World = new b2World(gravity);
    m_Manager = std::make_unique<EntityManager>();
    m_AssetManager = new AssetManager{};
    m_AssetManager->AddFont("ScoreFont", "arial.ttf", 20);
}

void GameMatchState::AddPlayerBall(Entity* entity, std::shared_ptr<Player> player)
{
    player->AddBallToTeam(entity);
    entity->AddComponent<PhysicsComponent>(m_World, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody, isSensor::False);
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
    staticObj1 = m_Manager->AddEntity(b2Vec2{SCREEN_WIDTH/2, 30}, b2Vec2{SCREEN_WIDTH-70, WALL_THICKNESS});
    staticObj2 = m_Manager->AddEntity(b2Vec2{SCREEN_WIDTH/2, SCREEN_HEIGHT - 30}, b2Vec2{SCREEN_WIDTH-70, WALL_THICKNESS});
    staticObj3 = m_Manager->AddEntity(b2Vec2{30, SCREEN_HEIGHT/2}, b2Vec2{WALL_THICKNESS, SCREEN_HEIGHT - WALL_BUFFER});
    staticObj4 = m_Manager->AddEntity(b2Vec2{SCREEN_WIDTH-30, SCREEN_HEIGHT/2}, b2Vec2{WALL_THICKNESS, SCREEN_HEIGHT - WALL_BUFFER});
    staticObj1->AddComponent<PhysicsComponent>(m_World, ShapeType::RECT, b2BodyType::b2_staticBody, isSensor::False);
    staticObj1->AddComponent<SDLRectComponent>(m_Renderer);
    staticObj2->AddComponent<PhysicsComponent>(m_World, ShapeType::RECT, b2BodyType::b2_staticBody, isSensor::False);
    staticObj2->AddComponent<SDLRectComponent>(m_Renderer);
    staticObj3->AddComponent<PhysicsComponent>(m_World, ShapeType::RECT, b2BodyType::b2_staticBody, isSensor::False);
    staticObj3->AddComponent<SDLRectComponent>(m_Renderer);
    staticObj4->AddComponent<PhysicsComponent>(m_World, ShapeType::RECT, b2BodyType::b2_staticBody, isSensor::False);
    staticObj4->AddComponent<SDLRectComponent>(m_Renderer);
}
