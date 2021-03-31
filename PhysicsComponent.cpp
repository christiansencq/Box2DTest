#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(float w, float h, float x, float y, b2World* world, bool dynamic)
 : mWidth(w), mHeight(h), physWorld(world), isDynamic(dynamic)
{
    b2BodyDef bodyDef;
    if (dynamic)
    {
        bodyDef.type = b2_dynamicBody;
    }
    bodyDef.position.Set(x, y);
    physBody = physWorld->CreateBody(&bodyDef);

    b2PolygonShape myShape;
    myShape.SetAsBox(w/2.0, h/2.0);

    if (dynamic)
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &myShape;
        fixtureDef.density = 0.1f;
        fixtureDef.friction = 0.1f;
        physBody->CreateFixture(&fixtureDef);
    }
    else
    {
        physBody->CreateFixture(&myShape, 0.0f);
    }
//    std::cout << "w/in PhysComp X: " << physBody->GetPosition().x << "\n";
//    std::cout << "w/in PhysComp Y: " << physBody->GetPosition().y << "\n";
}

PhysicsComponent::~PhysicsComponent()
{
    physWorld->DestroyBody(physBody);
}

void PhysicsComponent::Initialize()
{

}

void PhysicsComponent::HandleKeyPress(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_UP:
        {
            std::cout << "key up" << std::endl;
            b2Vec2 upVec {0.0f, 100.0f};
            physBody->ApplyForceToCenter(upVec, false);
            physBody->ApplyForceToCenter(upVec, false);
            break;
        }
        default:
            break;
    }
}

void PhysicsComponent::HandleKeyRelease(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_UP:
        {
            std::cout << "key up" << std::endl;
            b2Vec2 upVec {0.0f, 100.0f};
            physBody->ApplyForceToCenter(upVec, false);
            physBody->ApplyForceToCenter(upVec, false);
            break;
        }
        default:
            break;
    }
}


void PhysicsComponent::Update()
{
    //physWorld = world;
    //DO I NEED TO STEP THE WORLD IN HERE?  WOuld have to have the same parameters as all interacting worlds, seems clumsy.
    //Or pass in the Stepped- World from where this is called?
    //std::cout << "physComp X " << physBody->GetPosition().x << "\n";
    //std::cout << "physComp Y " << physBody->GetPosition().y << "\n";
}

void PhysicsComponent::Render(SDL_Renderer* renderer)
{
    
}

void PhysicsComponent::printType() const
{
    std::cout << "Component: " << type << std::endl;   
}