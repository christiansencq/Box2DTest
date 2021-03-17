#include "PhysicsState.h"
#include "Constants.h"


PhysicsState::PhysicsState(SDL_Renderer* renderer) : mnoptrrenderer(renderer),
timeStep(1/60.0f), velocityIterations(2), positionIterations(6)
{
    b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
    world = new b2World(gravity);

    mGroundBody = new PhysicsEntity(100.0f, 20.0f, 0.0f, -10.0f, world, false);
    mMovingBody = new PhysicsEntity(1.0f, 1.0f, 0.0f, 4.0f, world, true);
}

PhysicsState::~PhysicsState()
{
    delete world;
}

void PhysicsState::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            App::Singleton().QuitApp();
    }
}

void PhysicsState::update()
{
    world->Step(timeStep, velocityIterations, positionIterations);
    
    std::cout << "X " << mMovingBody->GetPhysBody()->GetPosition().x << "\n";
    std::cout << "Y " << mMovingBody->GetPhysBody()->GetPosition().y << "\n";
}

void PhysicsState::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    

    //Rendering
    SDL_RenderPresent(renderer);
}