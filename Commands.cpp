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
    owningComponent->physicsComp->SetThrusting(true);
}

void ForwardThrustCommand::executeRelease()
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