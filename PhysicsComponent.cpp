#include "PhysicsComponent.h"

//Take out name from the constructor.
PhysicsComponent::PhysicsComponent(b2World* world, bool dynamic)
 : isThrusting(false), turn(TurnDir::NONE), physWorld(world), isDynamic(dynamic), shapeType(ShapeType::RECT)
{
    
}

PhysicsComponent::PhysicsComponent(b2World* world, bool dynamic, ShapeType shape)
 : isThrusting(false), turn(TurnDir::NONE), physWorld(world), isDynamic(dynamic), shapeType(shape)
{
    
}

PhysicsComponent::PhysicsComponent(b2World* world, bool dynamic, std::string name, ShapeType shape)
 : isThrusting(false), turn(TurnDir::NONE), physWorld(world), isDynamic(dynamic), shapeType(shape)
{
    
}

PhysicsComponent::~PhysicsComponent()
{
    physWorld->DestroyBody(physBody);
}

void PhysicsComponent::Initialize()
{
    PixelW = owner->GetPixelSize().x;
    PixelH = owner->GetPixelSize().y;
    mRadius = owner->GetPixelSize().x;
    PixelX = owner->GetPixelPos().x;
    PixelY = owner->GetPixelPos().y;
    //CREATE BODY.
    CreateBody();
    //CREATE SHAPE & FIXTURE
    switch (shapeType)
    {
        case ShapeType::RECT:
            MakeRectShape();
            break;
        case ShapeType::CIRCLE:
            MakeCircleShape();
            break; 
        default:
            break;
    }
}

void PhysicsComponent::CreateBody()
{ 
    b2BodyDef bodyDef;
    bodyDef.position.Set(PixelX*P2M, PixelY*P2M);
    if (isDynamic)
    {
        bodyDef.type = b2_dynamicBody;
    }
    physBody = physWorld->CreateBody(&bodyDef);
}

void PhysicsComponent::MakeCircleShape()
{
    b2CircleShape shape;
    //The Shape Coordinates are related to the Body.  0.0 will be centered around the body.
    shape.m_p.Set(0.0f, 0.0f);
//    shape.m_p.Set(PixelX*P2M, PixelY*P2M);
    shape.m_radius = mRadius/2 * P2M;
    GenerateFixture(&shape);
}

void PhysicsComponent::MakeRectShape()
{
    b2PolygonShape shape;
    shape.SetAsBox(P2M * PixelW / 2.0, P2M * PixelH / 2.0);
    GenerateFixture(&shape);
}

//Change to AddFixtureToShape
void PhysicsComponent::GenerateFixture(b2Shape* shape)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 0.2f;
    fixtureDef.friction = 0.1f;
    //fixtureDef.restitution = 0.1f;
    // fixtureDef.filter.categoryBits = kFilterCategorySolidObject;
    // fixtureDef.filter.maskBits = 0xffff;
    physBody->CreateFixture(&fixtureDef);
}

void PhysicsComponent::Update()
{
    if (isThrusting && isDynamic)
    {
        std::cout << "IsThrusting" << "\n";
        //Get the Unit vector of my Object's angle.  
        b2Vec2 currentVec { 2*cos(physBody->GetAngle()), 2*sin(physBody->GetAngle())};   
        physBody->ApplyForceToCenter(currentVec, true);
    }

    if (turn == TurnDir::LEFT)
    {
        physBody->SetTransform(physBody->GetPosition(), physBody->GetAngle() - TURNSPEED);
    }
    else if (turn == TurnDir::RIGHT)
    {
        physBody->SetTransform(physBody->GetPosition(), physBody->GetAngle() + TURNSPEED);        
    }
}

void PhysicsComponent::printType() const
{
    std::cout << "Component: " << type << std::endl;   
}

void PhysicsComponent::SetTurning(TurnDir turning) 
{
    /*  Currently there is an issue with the rotating velocity.
        May want to 'SetFixedRotation' for the duration of a Turn.  */
//    if (turning != TurnDir::NONE)
//         physBody->SetFixedRotation(true);
//    else
//         physBody->SetFixedRotation(false);
    turn = turning; 
} 