#include "Commands.h"

#include "KeyInputComponent.h"

#include <iostream>

ForwardThrustCommand::ForwardThrustCommand()
{

}

void ForwardThrustCommand::Initialize()
{ 
    std::cout << "FwdThrust OwningComponent exists? " << owningComponent << "\n";
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
    std::cout << "LftTurn OwningComponent exists? " << owningComponent << "\n";
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
    std::cout << "RightTurn OwningComponent exists? " << owningComponent << "\n";
}

void RightTurnCommand::executePress() 
{
    owningComponent->physicsComp->SetTurning(TurnDir::RIGHT);
}

void RightTurnCommand::executeRelease()
{
    owningComponent->physicsComp->SetTurning(TurnDir::NONE);
} 