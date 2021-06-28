#include "Commands.h"

#include "../Components/KeyInputComponent.h"
#include "../Entity.h"
ForwardThrustCommand::ForwardThrustCommand()
{

}

void ForwardThrustCommand::Initialize()
{ 
    //owningComponent->m_ActionMap[Actions::FORWARD] = this;
    owningComponent->AssignAction(Actions::FORWARD, this);
}

void ForwardThrustCommand::executePress()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrustDirection(ThrustDir::FORWARD);    
    //owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrusting(true);
}

void ForwardThrustCommand::executeRelease()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrusting(false);
}


BackwardThrustCommand::BackwardThrustCommand()
{
    
}

void BackwardThrustCommand::Initialize()
{
//    owningComponent->m_ActionMap[Actions::BACKWARD] = this;
    owningComponent->AssignAction(Actions::BACKWARD, this);
}

void BackwardThrustCommand::executePress()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrustDirection(ThrustDir::BACKWARD);    
    //owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrusting(true);
}

void BackwardThrustCommand::executeRelease()
{
    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrusting(false);
}


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

/*

void LeftFixedTurnCommand::LeftFixedTurnCommand()
{
    
}

void LeftFixedTurnCommand::Initialize()
{

}

void LeftFixedTurnCommand::executePress()
{

}

void LeftFixedTurnCommand::executeRelease()
{

}


*/





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
