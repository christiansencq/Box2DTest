#include "Commands.h"

#include "KeyInputComponent.h"

#include <iostream>

ForwardThrustCommand::ForwardThrustCommand()
{

}

void ForwardThrustCommand::Initialize()
{ 
    owningComponent->ActionMap[Actions::FORWARD] = this;
}

void ForwardThrustCommand::executePress()
{
    owningComponent->physicsComp->SetThrustDirection(ThrustDir::FORWARD);    
    owningComponent->physicsComp->SetThrusting(true);
}

void ForwardThrustCommand::executeRelease()
{
    owningComponent->physicsComp->SetThrusting(false);
}


BackwardThrustCommand::BackwardThrustCommand()
{
    
}

void BackwardThrustCommand::Initialize()
{
    owningComponent->ActionMap[Actions::BACKWARD] = this;
}

void BackwardThrustCommand::executePress()
{
    owningComponent->physicsComp->SetThrustDirection(ThrustDir::BACKWARD);    
    owningComponent->physicsComp->SetThrusting(true);
}
void BackwardThrustCommand::executeRelease()
{
    owningComponent->physicsComp->SetThrusting(false);
}


LeftTurnCommand::LeftTurnCommand()
{ 

}

void LeftTurnCommand::Initialize()
{ 
    owningComponent->ActionMap[Actions::LEFT] = this;
}

void LeftTurnCommand::executePress() 
{
    owningComponent->physicsComp->SetTurning(TurnDir::LEFT);
}

void LeftTurnCommand::executeRelease()
{
    owningComponent->physicsComp->SetTurning(TurnDir::NONE);
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
    owningComponent->ActionMap[Actions::RIGHT] = this;
}

void RightTurnCommand::executePress() 
{
    owningComponent->physicsComp->SetTurning(TurnDir::RIGHT);
}

void RightTurnCommand::executeRelease()
{
    owningComponent->physicsComp->SetTurning(TurnDir::NONE);
} 