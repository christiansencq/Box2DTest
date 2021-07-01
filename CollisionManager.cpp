#include "CollisionManager.h"
#include <iostream>

void CollisionManager::BeginContact(b2Contact* contact)
{
//Called when fxitures BEGIN touching.

    std::cout << "A contact has begun. \n";

    // b2Fixture* fixA = contact->GetFixtureA();
    // b2Fixture* fixB = contact->GetFixtureB();
    // if (fixA->GetUserData()->isScorer 
    //Check if a score has been made.  If so, set GoalMade to TRUE in GameMatchState. 
    //
    // //Test if the combined bits are the same as the combined bits of P1sGoalZone and Puck's masks.
    // if (fixA->GetFilterData().categoryBits | fixB->GetFilterData().categoryBits ) 
    // {
    // }
}


void CollisionManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
//Called before the Solver.k
}

void CollisionManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

void CollisionManager::EndContact(b2Contact* contact)
{
//Called when fixtures stop touching.
}
