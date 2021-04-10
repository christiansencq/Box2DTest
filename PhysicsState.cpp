#include "PhysicsState.h"

PhysicsState::PhysicsState(SDL_Renderer* renderer)
 : mnoptrrenderer(renderer), timeStep(1/30.0f), velocityIterations(2), positionIterations(6)
{
    b2Vec2 gravity = b2Vec2(0.0f, -0.05f);
    world = new b2World(gravity);
    
    manager = new EntityManager();

    //Need a Copy Constructor for Entity?
    Entity& movingObject{manager->AddEntity(std::string("Mover"))};

    /*
    Set the ScreenPos and dimensions (2d) for movingObject

    If we consider the screen size is 1280 x 720, and if we want to 
    keep physics coords under 5k, then we need to scale up
    pixelX = 100, pixelY = 200 ---- physX = 10, physY = 20 

    Could use scaling factor of 0.1
    In which case a pixel coordinate of 350, 500
    would yield phys position of 35.0, 50.0

    Objects should move approximately(on average) 1 physics unit per frame, ideally.
    The minimum should be 0.1 units and max is 10 units.    
    */

    movingObject.SetPixelPos(b2Vec2{350, 500});
    movingObject.SetPixelSize(b2Vec2{20, 20});
    movingObject.ConvertPixelPosToPhysPos();
    movingObject.ConvertPixelSizeToPhysSize();
    //Calculate the Position and Size coordinates converted to the PhysicsScale.

    movingObject.AddComponent<PhysicsComponent>(movingObject.GetPhysW(), movingObject.GetPhysH(), 
                                                movingObject.GetPhysX(), movingObject.GetPhysY(), 
                                                world, true);
    movingObject.AddComponent<SDLRectComponent>(movingObject.GetPixelX(), movingObject.GetPixelY(),
                                                movingObject.GetPixelWidth(), movingObject.GetPixelHeight());

    Entity& staticObject{manager->AddEntity(std::string("Floor"))};
    staticObject.SetPixelPos(b2Vec2{100, 0});
    staticObject.SetPixelSize(b2Vec2{800, 10});
    staticObject.ConvertPixelPosToPhysPos();
    staticObject.ConvertPixelSizeToPhysSize();
    staticObject.AddComponent<PhysicsComponent>(staticObject.GetPhysW(), staticObject.GetPhysH(), 
                                                staticObject.GetPhysX(), staticObject.GetPhysY(), 
                                                world, false);
    staticObject.AddComponent<SDLRectComponent>(staticObject.GetPixelX(), staticObject.GetPixelY(), 
                                                staticObject.GetPixelWidth(), staticObject.GetPixelHeight());
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
    world->Step(timeStep, velocityIterations, positionIterations); 
    manager->Update();

    //std::cout << "X OF MOVING BODY " << manager->GetEntityByName(std::string("Mover"))->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().x << std::endl;
    std::cout << "PhysY OF MOVING BODY " << manager->GetEntityByName(std::string("Mover"))->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().y << std::endl;
    std::cout << "ScreenY OF MOVING BODY " << manager->GetEntityByName(std::string("Mover"))->GetPixelY() << std::endl;
}

void PhysicsState::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x22, 0x99, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    
    if (!manager->HasEntities())
    {
        std::cout << "There are no entities!";
        return;
    }

    manager->Render(renderer);

    //Rendering
    SDL_RenderPresent(renderer);
}