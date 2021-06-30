#include "GoalZoneComponent.h"
#include "../Entity.h"

//When merging with Physics object (maybe use a TurnIntoGoalMethod() or inheritance)
GoalZoneComponent::GoalZoneComponent(b2World* world, std::shared_ptr<Player> player)
    : m_Player(player), m_PhysWorld(world) 
{

}

GoalZoneComponent::~GoalZoneComponent()
{
    m_PhysWorld->DestroyBody(m_PhysBody);
}

void GoalZoneComponent::Initialize()
{
    m_Width = owner->GetPixelSize().x;
    m_Height = owner->GetPixelSize().y;

    CreateBody();
    CreateRectShape();
}

//void GoalZoneComponent::Update( b2body physBody) { }
void GoalZoneComponent::Update()
{
    //This should go in a ContactListener probably.
    for ( b2ContactEdge* ce = m_PhysBody->GetContactList(); ce; ce = ce->next)
    {
        
        // b2Contact* c = ce->contact;
        // // b2Filter filtA = c->GetFixtureA()->GetFilterData();
        // b2Filter filtB = c->GetFixtureB()->GetFilterData();

        std::cout << "Score being made. \n";
        owner->SignalManagerToReset();
        m_Player->IncrementScore(1);
   }
}

void GoalZoneComponent::CreateBody()
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(owner->GetPixelPos().x * P2M, owner->GetPixelPos().y * P2M);
    bodyDef.type = b2_staticBody;
    m_PhysBody = m_PhysWorld->CreateBody(&bodyDef);
}

void GoalZoneComponent::CreateRectShape()
{
    b2PolygonShape shape;
    shape.SetAsBox(P2M * m_Width/2.0f, P2M * m_Height/2.0f);
    GenerateFixture(&shape);
} 

void GoalZoneComponent::GenerateFixture(b2Shape* shape)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.isSensor = true;
    m_PhysBody->CreateFixture(&fixtureDef);
}

