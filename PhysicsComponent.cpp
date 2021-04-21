#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(int pixelX, int pixelY, int pixelW, int pixelH,  
                                   b2World* world, bool dynamic)
 : PixelX(pixelX), PixelY(pixelY), PixelW(pixelW), PixelH(pixelH), 
   isThrusting(false), turn(TurnDir::NONE), physWorld(world), isDynamic(dynamic)
{
    shapeType = "rect";
    b2BodyDef bodyDef;
    bodyDef.position.Set(PixelX*P2M, PixelY*P2M);
    if (isDynamic)
    {
        bodyDef.type = b2_dynamicBody;
    }
    physBody = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(P2M * PixelW / 2.0, P2M * PixelH / 2.0);

    b2FixtureDef fixtureDef;
    if (isDynamic)
    {
        density = 0.1f;
        friction = 0.1f;
    }
    else
    {
        density = 0.0f;
        //friction = 0.0f;
    }

    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;

    physFixture = physBody->CreateFixture(&fixtureDef);
}

PhysicsComponent::PhysicsComponent(int pixelX, int pixelY, int pixelR, b2World* world, bool dynamic)
 : PixelX(pixelX), PixelY(pixelY), PixelR(pixelR), 
   isThrusting(false), physWorld(world), isDynamic(dynamic)
{
    shapeType = "circle";
    b2BodyDef bodyDef;
    bodyDef.position.Set(PixelX*P2M, PixelY*P2M);
    if (isDynamic)
    {
        bodyDef.type = b2_dynamicBody;
    }
    physBody = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 10.0f;

    b2FixtureDef fixtureDef;
    if (isDynamic)
    {
        density = 0.1f;
        friction = 0.1f;
    }
    else
    {
        density = 0.0f;
        //friction = 0.0f;
    }

    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;

    physFixture = physBody->CreateFixture(&fixtureDef);
}

PhysicsComponent::~PhysicsComponent()
{
    physWorld->DestroyBody(physBody);
}

void PhysicsComponent::Initialize()
{

}

void PhysicsComponent::HandleKeyPress(const SDL_Keycode key)
{

}

void PhysicsComponent::HandleKeyRelease(const SDL_Keycode key)
{

}

void PhysicsComponent::Update()
{
    //std::cout << "Is it thrusting? " << isThrusting << "\n";
    if (isThrusting && isDynamic)
    {
        std::cout << "Thrusting" << std::endl;
//        b2Vec2 upVec {0.0f, -4.5f};
        //Get the Unit vector of my Object's angle.  
        b2Vec2 currentVec { cos(physBody->GetAngle()), 2 * sin(physBody->GetAngle())};
        
        physBody->ApplyForceToCenter(currentVec, true);
    }

    if (turn == TurnDir::LEFT)
    {
        // physBody->ApplyTorque(1, true);
        physBody->SetTransform(physBody->GetPosition(), physBody->GetAngle() - TURNSPEED);
    }
    else if (turn == TurnDir::RIGHT)
    {
        // physBody->ApplyTorque(-1, true);
        physBody->SetTransform(physBody->GetPosition(), physBody->GetAngle() + TURNSPEED);        
    }

}

void PhysicsComponent::Render(SDL_Renderer* renderer)
{
    
}

void PhysicsComponent::printType() const
{
    std::cout << "Component: " << type << std::endl;   
}