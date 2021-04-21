#include "PhysicsState.h"

PhysicsState::PhysicsState(SDL_Renderer* renderer, SDL_Surface* surface)
 : mnoptrrenderer(renderer), mnoptrsurface(surface), timeStep(1/30.0f), velocityIterations(2), positionIterations(6), ticksLastFrame(0)
 {
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    world = new b2World(gravity);
    manager = new EntityManager();

    //Need a Copy Constructor for Entity?
    Entity* movingObj1{manager->AddEntity(std::string("Mover"))};
//    Entity* movingObj2{manager->AddEntity(std::string("Mover2"))};

    //Set the ScreenPos and dimensions (2d) for movingObject.
    movingObj1->SetPixelPos(b2Vec2{350, 570});
    movingObj1->SetPixelSize(b2Vec2{70, 50});

    //Shouldn't be any reason that PhysicsComoponent or SDLRect component NEED an initial position or size.  Should be able to pull these from Entity.xc2w
    movingObj1->AddComponent<PhysicsComponent>(350, 570, 70, 50, world, true);
    movingObj1->AddComponent<SDLRectComponent>(renderer, 70, 50);
    movingObj1->AddComponent<KeyInputComponent>();

    Entity* staticObj1{manager->AddEntity(std::string("Ceiling"))};
    Entity* staticObj2{manager->AddEntity(std::string("Floor"))};

    staticObj1->SetPixelPos(b2Vec2{100, 5});
    staticObj1->SetPixelSize(b2Vec2{SCREEN_WIDTH, 10});
    staticObj1->AddComponent<PhysicsComponent>(0, 5, SCREEN_WIDTH, 10, world, false);
    staticObj1->AddComponent<SDLRectComponent>(renderer, SCREEN_WIDTH, 10);

    staticObj2->SetPixelPos(b2Vec2{100, SCREEN_HEIGHT - 15});
    staticObj2->SetPixelSize(b2Vec2{SCREEN_WIDTH, 10});
    staticObj2->AddComponent<PhysicsComponent>(0, SCREEN_HEIGHT - 15, SCREEN_WIDTH, 10, world, false);
    staticObj2->AddComponent<SDLRectComponent>(renderer, SCREEN_WIDTH, 10);
}

PhysicsState::~PhysicsState()
{

    delete world;
    delete manager;
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
                    std::cout << "" << "\n";
                    break;

                default:
                    /* 
                    Actually, don't need to call EVERY input component.  
                    Have Entity Manager store a pointer to the 'active ball' & just call the input component of that object.
                    */

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
    //Add to renderer:
    manager->Render(renderer);
    }
    
    //Rendering
    SDL_RenderPresent(renderer);
}
