#include "Commands.h"

#include "../Components/KeyInputComponent.h"
#include "../Entity.h"

// ------------- FORWARD -------------------
ForwardThrustCommand::ForwardThrustCommand()
{

}

void ForwardThrustCommand::Initialize()
{ 
    m_PhysComp = owningComponent->GetOwner()->GetComponent<PhysicsComponent>();
    owningComponent->AssignAction(Actions::FORWARD, this);
}

void ForwardThrustCommand::executePress()
{
    m_PhysComp->SetThrustDirection(ThrustDir::FORWARD);    
}

void ForwardThrustCommand::executeRelease()
{
    m_PhysComp->SetThrusting(false);
}

void ForwardThrustCommand::Update() 
{
}

// ------------- BACKWARD -------------------
BackwardThrustCommand::BackwardThrustCommand()
{
}

void BackwardThrustCommand::Initialize()
{
    m_PhysComp = owningComponent->GetOwner()->GetComponent<PhysicsComponent>();
    owningComponent->AssignAction(Actions::BACKWARD, this);
}

void BackwardThrustCommand::executePress()
{
    m_PhysComp->SetThrustDirection(ThrustDir::BACKWARD);
    //owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetThrustDirection(ThrustDir::BACKWARD);    
}

void BackwardThrustCommand::executeRelease()
{
    m_PhysComp->SetThrusting(false);
}

void BackwardThrustCommand::Update() 
{
}

// ------------- LEFT -------------------
LeftTurnCommand::LeftTurnCommand()
{ 
}

void LeftTurnCommand::Initialize()
{ 
    m_PhysComp = owningComponent->GetOwner()->GetComponent<PhysicsComponent>();
    owningComponent->AssignAction(Actions::LEFT, this);
}

void LeftTurnCommand::executePress() 
{
    //owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::LEFT);
    m_PhysComp->SetTurning(TurnDir::LEFT);
}

void LeftTurnCommand::executeRelease()
{
    //owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::NONE);
    m_PhysComp->SetTurning(TurnDir::NONE);
}

void LeftTurnCommand::Update()
{
}

// ------------- RIGHT -------------------
RightTurnCommand::RightTurnCommand()
{ 
}

void RightTurnCommand::Initialize()
{ 
    m_PhysComp = owningComponent->GetOwner()->GetComponent<PhysicsComponent>();
    owningComponent->AssignAction(Actions::RIGHT, this);
}

void RightTurnCommand::executePress() 
{
    //owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::RIGHT);
    m_PhysComp->SetTurning(TurnDir::RIGHT);
}

void RightTurnCommand::executeRelease()
{
//    owningComponent->GetOwner()->GetComponent<PhysicsComponent>()->SetTurning(TurnDir::NONE);
    m_PhysComp->SetTurning(TurnDir::NONE);
} 

void RightTurnCommand::Update()
{
}

// -------------- IMPULSE -----------------
ImpulseFwdCommand::ImpulseFwdCommand()
{
}

void ImpulseFwdCommand::Initialize()
{
    m_PhysComp = owningComponent->GetOwner()->GetComponent<PhysicsComponent>();
    owningComponent->AssignAction(Actions::RIGHT, this);
}

void ImpulseFwdCommand::executePress()
{
    if (!isCoolingDown)
    {
        //m_PhysComp->        
    }
}

void ImpulseFwdCommand::executeRelease()
{
}

void ImpulseFwdCommand::Update()
{
    if (isCoolingDown)
    {
        cur_cooldown -= 1.f/FPS;
    }
}
