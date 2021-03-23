#include "PhysicsState.h"
#include "Constants.h"


PhysicsState::PhysicsState(SDL_Renderer* renderer)
 : mnoptrrenderer(renderer), timeStep(1/30.0f), velocityIterations(2), positionIterations(6)
{
    b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
    world = new b2World(gravity);
    
    manager = new EntityManager();


    //Need a Copy Constructor for Entity?

    Entity& movingObject{manager->AddEntity(std::string("Mover"))};
    movingObject.AddComponent<PhysicsComponent>(1.0f, 1.0f, 0.0f, -10.0f, world, true);

    Entity& staticObject{manager->AddEntity(std::string("Floor"))};
    staticObject.AddComponent<PhysicsComponent>(50.0f, 10.0f, 0.0f, 10.0f, world, false);
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
    }
}

void PhysicsState::Update()
{
    world->Step(timeStep, velocityIterations, positionIterations); 
    manager->Update();

    std::cout << "X OF MOVING BODY " << manager->GetEntityByName(std::string("Mover"))->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().x << std::endl;
    std::cout << "Y OF MOVING BODY " << manager->GetEntityByName(std::string("Mover"))->GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().y << std::endl;
}

void PhysicsState::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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