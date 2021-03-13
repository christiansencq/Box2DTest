#include "PhysicsState.h"
#include "Constants.h"

PhysicsState::PhysicsState(SDL_Renderer* renderer) : mnoptrrenderer(renderer)
{
    gravity.Set(0.0f, -10.0f);
    mWorld = new b2World(gravity);

    mGroundBody = createStaticBody(*mWorld);
    mMovingBody = createDynamicBody(*mWorld);
}

PhysicsState::~PhysicsState()
{

    mWorld->DestroyBody(mGroundBody);
    mWorld->DestroyBody(mMovingBody);
    delete mWorld;
}

b2Body* PhysicsState::createStaticBody(b2World& world)
{
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* newBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    newBody->CreateFixture(&groundBox, 0.0f);

    return newBody;
}

b2Body* PhysicsState::createDynamicBody(b2World& world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* newBody = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    newBody->CreateFixture(&fixtureDef);

    return newBody;
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
    mWorld->Step(timeStep, velocityIterations, positionIterations);
    //std::cout << "Step: " << timeStep << std::endl;

    b2Vec2 position = mMovingBody->GetPosition();
    float angle = mMovingBody->GetAngle(); 

    printf("X, Y, Angle: %4.2f %4.2f %4.2f\n", position.x, position.y, angle);

//    movingBody->update(); 

}

void PhysicsState::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Rendering
    SDL_RenderPresent(renderer);
}