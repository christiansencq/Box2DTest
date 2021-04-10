#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(float w, float h, float x, float y, 
                                   b2World* world, bool dynamic)
 : mWidth(w), mHeight(h), mPhysX(x), mPhysY(y), 
   isThrusting(false), physWorld(world), isDynamic(dynamic)
{

}

PhysicsComponent::PhysicsComponent(b2Vec2 physSize, b2Vec2 physPos, b2World* world, bool dynamic)
    : mWidth(physSize.x), mHeight(physSize.y), mPhysX(physPos.x), mPhysY(physPos.y), 
    isThrusting(false), physWorld(world), isDynamic(dynamic)
{

}

PhysicsComponent::~PhysicsComponent()
{
    physWorld->DestroyBody(physBody);
}

void PhysicsComponent::Initialize()
{
    b2BodyDef bodyDef;
    if (isDynamic)
    {
        bodyDef.type = b2_dynamicBody;
    }
    bodyDef.position.Set(mPhysX, mPhysY);
    physBody = physWorld->CreateBody(&bodyDef);

    b2PolygonShape myShape;
    myShape.SetAsBox(mWidth/2.0, mHeight/2.0);

    if (isDynamic)
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
}

void PhysicsComponent::HandleKeyPress(const SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_UP:
        {
            isThrusting = true;
            break;
        }
        default:
            break;
    }
}

void PhysicsComponent::HandleKeyRelease(const SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_UP:
        {
            isThrusting = false;
            break;
        }
        default:
             break;
    }
}

void PhysicsComponent::Update()
{
    //std::cout << "Is it thrusting? " << isThrusting << "\n";
    if (isThrusting)
    {
        std::cout << "Thrusting" << std::endl;
        b2Vec2 upVec {0.0f, 10.0f};
        physBody->ApplyForceToCenter(upVec, true);
    }

    //Only worry about updating the entity's screen position if this is actually doing something. 
    if (physBody->IsAwake())
    {
        b2Vec2 newPos{physBody->GetPosition().x * 10, physBody->GetPosition().y * 10};
        owner->SetPixelPos(newPos);
    }
}

void PhysicsComponent::Render(SDL_Renderer* renderer)
{
    
}

void PhysicsComponent::printType() const
{
    std::cout << "Component: " << type << std::endl;   
}