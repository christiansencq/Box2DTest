#include "PhysicsComponent.h"
#include "../Entity.h"


PhysicsComponent::PhysicsComponent(b2World* world, ShapeType shape, b2BodyType body_type)
 : m_PhysWorld(world), m_ShapeType(shape), m_BodyType(body_type), m_BodyData(new BodyData())
{
    // m_BodyData = std::make_unique<BodyData>();
    
    
}

PhysicsComponent::~PhysicsComponent()
{
    m_PhysWorld->DestroyBody(m_PhysBody);
    delete m_BodyData; 
}

void PhysicsComponent::SetData(bool scorer)
{
    m_BodyData->isScorer = scorer;
    m_PhysBody->SetUserData(m_BodyData);
}


void PhysicsComponent::Initialize()
{
    m_Radius = owner->GetPixelSize().x;

    //CREATE BODY.
    CreateBody();
    //CREATE SHAPE & FIXTURE
    switch (m_ShapeType)
    {
        case ShapeType::RECT:
            MakeRectShape();
            break;
        case ShapeType::CIRCLE:
            MakeCircleShape(0.0f, 0.0f);
            break;  
        default:
            break;
    }
}

void PhysicsComponent::CreateBody()
{ 
    b2BodyDef bodyDef;
    bodyDef.position.Set(owner->GetPixelPos().x*P2M, owner->GetPixelPos().y*P2M);
    //bodyDef.angle.Set(owner->GetAngle());
    bodyDef.type = m_BodyType;
    m_PhysBody = m_PhysWorld->CreateBody(&bodyDef);
}

void PhysicsComponent::MakeCircleShape(float x_offset, float y_offset)
{
    b2CircleShape shape;
    //Shape Coordinates are relative to Body.  0.0 is centered around the body.
    shape.m_p.Set(x_offset, y_offset);
    shape.m_radius = m_Radius/2 * P2M;
    GenerateFixture(&shape);
}

void PhysicsComponent::MakeRectShape()
{
    b2PolygonShape shape;
    shape.SetAsBox(P2M * owner->GetPixelSize().x / 2.0, 
                   P2M * owner->GetPixelSize().y / 2.0);
    GenerateFixture(&shape);
}


//Change to AddFixtureToShape
// Remove this.  Should not need to keep fixture past the addition fo the shape (for now)
void PhysicsComponent::GenerateFixture(b2Shape* shape)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = m_Density;
    fixtureDef.friction = m_Friction;
    fixtureDef.restitution = 0.1f;
    // fixtureDef.isSensor = (m_IsSensor == isSensor::True);
    // fixtureDef.filter.categoryBits = m_colCategory;
    // fixtureDef.filter.maskBits = m_colMask;
    m_PhysBody->CreateFixture(&fixtureDef);
}

void PhysicsComponent::Update()
{
    if (isThrusting && (m_BodyType == b2_dynamicBody) )
    {
        //Get the Unit vector of my Object's angle. 
//        std::cout << "ThrustingVec Force (" << m_ThrustingVec.x << ", " << m_ThrustingVec.y << ")\n";
//        std::cout << "Owner X " << owner->GetPixelPos().x << ", Y " << owner->GetPixelPos().y << " \n";
//        std::cout << "PhysBody X " << m_PhysBody->GetPosition().x << ", Y " << m_PhysBody->GetPosition().y << "\n";
        m_PhysBody->ApplyForceToCenter(m_ThrustingVec, true);
    }

    if (m_Turn == TurnDir::LEFT)
    {
        m_PhysBody->SetTransform(m_PhysBody->GetPosition(), m_PhysBody->GetAngle() - m_TurnSpeed);
    }
    else if (m_Turn == TurnDir::RIGHT)
    {
        m_PhysBody->SetTransform(m_PhysBody->GetPosition(), m_PhysBody->GetAngle() + m_TurnSpeed);        
    }
    owner->SetPixelPos(b2Vec2 {m_PhysBody->GetPosition().x * M2P, m_PhysBody->GetPosition().y * M2P });
    owner->SetAngle(m_PhysBody->GetAngle());
}

void PhysicsComponent::SetFixedTurning(TurnDir turning, bool fixed)
{
    m_PhysBody->SetFixedRotation(fixed);
    m_Turn = turning; 
}

void PhysicsComponent::SetTurning(TurnDir turning) 
{
    /*  Currently there is an issue with the rotating velocity.
        May want to 'SetFixedRotation' for the duration of a m_Turn.  */

    if (m_Turn != TurnDir::NONE)
         m_PhysBody->SetFixedRotation(true);
    else
         m_PhysBody->SetFixedRotation(false);
    m_Turn = turning; 
} 

void PhysicsComponent::SetThrustDirection(ThrustDir dir)
{
    switch (dir)
    {
        case ThrustDir::FORWARD:
            m_ThrustingVec = { 2*cos(m_PhysBody->GetAngle()), 2*sin(m_PhysBody->GetAngle())};
            isThrusting = true;            
            break;
        case ThrustDir::BACKWARD:
            m_ThrustingVec = { -2*cos(m_PhysBody->GetAngle()), -2*sin(m_PhysBody->GetAngle())};
            isThrusting = true;
            break;            
        case ThrustDir::NONE:
            m_ThrustingVec = { 0, 0};
            isThrusting = false;
            break;            
    }
}

void PhysicsComponent::SetTransform(b2Vec2 pos, float angle)
{
    m_PhysBody->SetTransform(pos, angle);
}

