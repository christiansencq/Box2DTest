#include "ContactManager.h"

void ContactManager::BeginContact(b2Contact* contact)
{
    //Check if a score has been made.  If so, set GoalMade to TRUE in GameMatchState. 
    b2Fixture* fixA = contact->GetFixtureA();
    b2Fixture* fixB = contact->GetFixtureB();
    
    //Test if the combined bits are the same as the combined bits of P1sGoalZone and Puck's masks.
    if (fixA->GetFilterData().categoryBits | fixB->GetFilterData().categoryBits ) 
    {
            
    }
}

void ContactManager::EndContact(b2Contact* contact)
{

}

void ContactManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void ContactManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}
