#include "Commands.h"

#include "../Components/KeyInputComponent.h"
#include "../Entity.h"

// ------------- FORWARD -------------------
ForwardThrustCommand::ForwardThrustCommand()
{

}

void ForwardThrustCommand::Initialize()
{ 
    owningComponent->AssignAction(Actions::FORWARD, this);
}

void ForwardThrustCommand::executePress()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrustDirection(ThrustDir::FORWARD);    
}

void ForwardThrustCommand::executeRelease()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrusting(false);
}

// ------------- BACKWARD -------------------
BackwardThrustCommand::BackwardThrustCommand()
{
    
}

void BackwardThrustCommand::Initialize()
{
    owningComponent->AssignAction(Actions::BACKWARD, this);
}

void BackwardThrustCommand::executePress()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrustDirection(ThrustDir::BACKWARD);    
}

void BackwardThrustCommand::executeRelease()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrusting(false);
}


// ------------- LEFT -------------------
LeftTurnCommand::LeftTurnCommand()
{ 

}

void LeftTurnCommand::Initialize()
{ 
//    owningComponent->m_ActionMap[Actions::LEFT] = this;
    owningComponent->AssignAction(Actions::LEFT, this);
}

void LeftTurnCommand::executePress() 
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::LEFT);
}

void LeftTurnCommand::executeRelease()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::NONE);
}

// ------------- RIGHT -------------------
RightTurnCommand::RightTurnCommand()
{ 

}

void RightTurnCommand::Initialize()
{ 
//    owningComponent->m_ActionMap[Actions::RIGHT] = this;
    owningComponent->AssignAction(Actions::RIGHT, this);
}

void RightTurnCommand::executePress() 
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::RIGHT);
}

void RightTurnCommand::executeRelease()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::NONE);
} 
