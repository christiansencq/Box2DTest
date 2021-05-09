#include "PhysicsState.h"

PhysicsState::PhysicsState(SDL_Renderer* renderer, SDL_Surface* surface)
 : mnoptrrenderer(renderer), mnoptrsurface(surface), timeStep(1/30.0f), velocityIterations(2), positionIterations(6), ticksLastFrame(0)
 {
    InitWorld();

    std::array<SDL_Keycode, 3> P1SwapKeys = { SDLK_i, SDLK_o, SDLK_p };
    std::array<SDL_Keycode, 4> P1ActionKeys = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };

    //Condense this all into methods per object.
    //Can use initializing format: manager, name, b2Vec2 position, float radius.
    movingObj1 = manager->AddEntity(std::string("P1Mover"), b2Vec2{350, 640}, 50.0f);
    movingObj1->AddComponent<PhysicsComponent>(world, true, ShapeType::CIRCLE);
    movingObj1->AddComponent<SDLCircleComponent>(renderer);
    movingObj1->AddComponent<KeyInputComponent>(P1ActionKeys);
    
    movingObj1->GetComponent<KeyInputComponent>()->AddCommand<ForwardThrustCommand>();
    movingObj1->GetComponent<KeyInputComponent>()->AddCommand<BackwardThrustCommand>();
    movingObj1->GetComponent<KeyInputComponent>()->AddCommand<LeftTurnCommand>();
    movingObj1->GetComponent<KeyInputComponent>()->AddCommand<RightTurnCommand>();

    movingObj2 = manager->AddEntity(std::string("P1Mover2"), b2Vec2{350, 480}, 50.0f);
    movingObj2->AddComponent<PhysicsComponent>(world, true, ShapeType::CIRCLE);
    movingObj2->AddComponent<SDLCircleComponent>(renderer);
    movingObj2->AddComponent<KeyInputComponent>(P1ActionKeys);

//    mO2InputComp = movingObj2->GetComponent<KeyInputComponent>();
    movingObj2->GetComponent<KeyInputComponent>()->AddCommand<ForwardThrustCommand>();
    movingObj2->GetComponent<KeyInputComponent>()->AddCommand<BackwardThrustCommand>();
    movingObj2->GetComponent<KeyInputComponent>()->AddCommand<LeftTurnCommand>();
    movingObj2->GetComponent<KeyInputComponent>()->AddCommand<RightTurnCommand>();

    movingObj3 = manager->AddEntity(std::string("P1Mover3"), b2Vec2{350, 320}, 50.0f);
    movingObj3->AddComponent<PhysicsComponent>(world, true, ShapeType::CIRCLE);
    movingObj3->AddComponent<SDLCircleComponent>(renderer);
    movingObj3->AddComponent<KeyInputComponent>(P1ActionKeys);

    movingObj3->GetComponent<KeyInputComponent>()->AddCommand<ForwardThrustCommand>();
    movingObj3->GetComponent<KeyInputComponent>()->AddCommand<BackwardThrustCommand>();
    movingObj3->GetComponent<KeyInputComponent>()->AddCommand<LeftTurnCommand>();
    movingObj3->GetComponent<KeyInputComponent>()->AddCommand<RightTurnCommand>();

    std::vector<Entity*> p1balls {movingObj1, movingObj2, movingObj3};
    P1 = new Player(1, p1balls, P1SwapKeys);
    manager->AddPlayer(P1);

    puckObj = manager->AddEntity(std::string("Puck"), b2Vec2{600, 150}, 25.0f);
    puckObj->AddComponent<PhysicsComponent>(world, true, ShapeType::CIRCLE);
    puckObj->AddComponent<SDLCircleComponent>(renderer, GREEN);

    staticObj1 = manager->AddEntity(std::string("Ceiling"), b2Vec2{SCREEN_WIDTH/2, 50}, b2Vec2{SCREEN_WIDTH-70, 10});
    staticObj2 = manager->AddEntity(std::string("Floor"), b2Vec2{SCREEN_WIDTH/2, SCREEN_HEIGHT - 60}, b2Vec2{SCREEN_WIDTH-70, 10});
    staticObj3 = manager->AddEntity(std::string("LWall"), b2Vec2{10, SCREEN_HEIGHT/2}, b2Vec2{10, SCREEN_HEIGHT -50});
    staticObj4 = manager->AddEntity(std::string("RWall"), b2Vec2{SCREEN_WIDTH-30, SCREEN_HEIGHT/2}, b2Vec2{10, SCREEN_HEIGHT - 50});
    staticObj1->AddComponent<PhysicsComponent>(world, false, ShapeType::RECT);
    staticObj1->AddComponent<SDLRectComponent>(renderer);
    staticObj2->AddComponent<PhysicsComponent>(world, false, ShapeType::RECT);
    staticObj2->AddComponent<SDLRectComponent>(renderer);
    staticObj3->AddComponent<PhysicsComponent>(world, false, ShapeType::RECT);
    staticObj3->AddComponent<SDLRectComponent>(renderer);
    staticObj4->AddComponent<PhysicsComponent>(world, false, ShapeType::RECT);
    staticObj4->AddComponent<SDLRectComponent>(renderer);
}

PhysicsState::~PhysicsState()
{
    delete world;
    delete manager;
}

void PhysicsState::InitWorld()
{
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    world = new b2World(gravity);
    manager = new EntityManager();
}

void PhysicsState::HandleEvents()
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
                    // std::cout << "aBallPixelViaMngr Coords: (" << P1->GetActive()->GetPixelPos().x << ", " << P1->GetActive()->GetPixelPos().y << ") \n";
                    // std::cout << "aBallPHysViaPixel Coords: (" << P2M * P1->GetActive()->GetPixelPos().x << ", " << P2M * P1->GetActive()->GetPixelPos().y << ") \n";
                    // std::cout << "aBallPhys Coords: (" << P1->GetActive()->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().x << ", " 
                    //                                    << P1->GetActive()->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().y  << ") \n";
                    // std::cout << "aBallPixelViaPhys Coords: (" << M2P * P1->GetActive()->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().x << ", " 
                    //                                    << M2P * P1->GetActive()->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().y  << ") \n";
                    // std::cout << "aBallPixelViaCirclComp Coords: (" << P1->GetActive()->GetComponent<SDLCircleComponent>()->GetPixelX() << ", " 
                    //                 << P1->GetActive()->GetComponent<SDLCircleComponent>()->GetPixelY()  << ") \n";
                    // std::cout << "aBallAngle: " << (180/3.14159) * P1->GetActive()->GetComponent<PhysicsComponent>()->GetPhysBody()->GetAngle() << "\n";
                    break;
                default:
                    manager->HandleKeyPress(event.key.keysym.sym);
                    break;
            }
            break;
        }

        case SDL_KEYUP:
        {
            manager->HandleKeyRelease(event.key.keysym.sym);
            break;
        }

        default:
            manager->HandleInput(event);
    }
}

void PhysicsState::Update()
{
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) 
    {
        SDL_Delay(timeToWait);
    }

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();

    world->Step(timeStep, velocityIterations, positionIterations); 
    manager->Update();
}

void PhysicsState::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x44, 0x99, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    
    if (!manager->HasEntities())
    {
        std::cout << "There are no entities!";
        return;
    }
    else
    {
        //Add stuff to renderer:
        manager->Render(renderer);
    }
    
    //Rendering
    SDL_RenderPresent(renderer);
}
