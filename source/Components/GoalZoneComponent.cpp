#include "GoalZoneComponent.h"
#include "../Entity.h"
#include "PlayerOwnerComponent.h"

//When merging with Physics object (maybe use a TurnIntoGoalMethod() or inheritance)
GoalZoneComponent::GoalZoneComponent(b2World* world, Player* player)
    : m_PhysWorld(world), m_CollisionData(CollisionData{}), m_Player(player)
{

}

// GoalZoneComponent::GoalZoneComponent(b2World* world)
//     : m_PhysWorld(world), m_CollisionData(CollisionData{})
// {
// }

GoalZoneComponent::~GoalZoneComponent()
{
    m_PhysWorld->DestroyBody(m_PhysBody);
}

void GoalZoneComponent::SetData(bool scorer)
{
    m_CollisionData.isScorer = false;
    m_PhysBody->SetUserData(&m_CollisionData);
}

void GoalZoneComponent::Initialize()
{
    m_Width = owner->GetPixelSize().x;
    m_Height = owner->GetPixelSize().y;

    CreateBody();
    CreateRectShape();
}

void GoalZoneComponent::Update()
{
    //This should go in a ContactListener probably.
    for ( b2ContactEdge* ce = m_PhysBody->GetContactList(); ce; ce = ce->next)
    {
        std::cout << "Get collision data.\n";
        b2Contact* c = ce->contact;
        b2Body* bodyA = c->GetFixtureA()->GetBody();
        b2Body* bodyB = c->GetFixtureB()->GetBody();
        CollisionData* dataA = (CollisionData*)bodyA->GetUserData();
        CollisionData* dataB = (CollisionData*)bodyB->GetUserData();
        std::cout << "Begin check for scorer.\n";

        if (dataA->isScorer || dataB->isScorer)
        {
            std::cout << "Score being made. \n";
            owner->SignalManagerToReset();
            if (owner->HasComponent<PlayerOwnerComponent>())
            {
                std::cout << "Found Player owner comp\n";
                std::cout << "[GZComp] Idnum : " << owner->GetComponent<PlayerOwnerComponent>()->GetPlayer()->GetPlayerID() << "\n\n";
                std::cout << "[GZComp] Current score " << owner->GetComponent<PlayerOwnerComponent>()->GetPlayer()->GetScore() << "\n\n";
            }

            std::cout << "[GZComp]Player ID from member " << m_Player->GetPlayerID() << "\n";
            std::cout << "[GZComp]Player score from member " << m_Player->GetScore() << "\n";
            // m_Player.IncrementScore();
            owner->GetComponent<PlayerOwnerComponent>()->GetPlayer()->IncrementScore();
        }
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

