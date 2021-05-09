#include "ActionComponent.h"

void ActionComponent::Initialize()
{
    physicsComp = owner->GetComponent<PhysicsComponent>();
}

void ActionComponent::ForwardPress()
{
    physicsComp->SetThrusting(true);
}

void ActionComponent::ForwardRelease()
{
    physicsComp->SetThrusting(false);
}

void ActionComponent::BackwardPress()
{

}

void ActionComponent::BackwardRelease()
{

}

void ActionComponent::LeftPress()
{
    physicsComp->SetTurning(TurnDir::LEFT);
}

void ActionComponent::LeftRelease()
{
    physicsComp->SetTurning(TurnDir::NONE);
}

void ActionComponent::RightPress()
{
    physicsComp->SetTurning(TurnDir::RIGHT);
}

void ActionComponent::RightRelease()
{
    physicsComp->SetTurning(TurnDir::NONE);
}