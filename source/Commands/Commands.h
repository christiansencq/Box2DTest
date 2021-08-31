#ifndef COMMANDS_H
#define COMMANDS_H

#include "Constants.h"
#include "../Components/PhysicsComponent.h"
/*
    Commands tell the KeyInputComponent where to put it.  
    I.E. to the button assigned for Fwd,Back,Left,Right, etc.

    TODO: move the assignment of owning component to Initialize argument, so that it can be private?
*/ 

class KeyInputComponent;


class Command
{
public:
    Command() {}
    virtual ~Command() {}
    virtual void Initialize() {}
    virtual void executePress() {}
    virtual void executeRelease() {}
    virtual void Update() {}

    KeyInputComponent* owningComponent;

private:

};


class ForwardThrustCommand : public Command
{

public:
    ForwardThrustCommand();
    virtual void Initialize() override;
    virtual void executePress() override;
    virtual void executeRelease() override;
    virtual void Update() override;

private:
    PhysicsComponent* m_PhysComp;


};

class BackwardThrustCommand : public Command
{
public:
    BackwardThrustCommand();
    virtual void Initialize() override;
    virtual void executePress() override;
    virtual void executeRelease() override;
    virtual void Update() override;

private:
    PhysicsComponent* m_PhysComp;

};

class LeftTurnCommand : public Command
{
public:
    LeftTurnCommand();
    virtual void Initialize() override;
    virtual void executePress() override;
    virtual void executeRelease() override;
    virtual void Update() override;

private:
    PhysicsComponent* m_PhysComp;


};

class RightTurnCommand : public Command
{
public:
    RightTurnCommand();
    virtual void Initialize() override;
    virtual void executePress() override;
    virtual void executeRelease() override;
    virtual void Update() override;

private:
    PhysicsComponent* m_PhysComp;

};

//Add a version of this with an Update command.
class ImpulseFwdCommand : public Command
{
public:
    ImpulseFwdCommand();
    virtual void Initialize() override;
    virtual void executePress() override;
    virtual void executeRelease() override;
    virtual void Update() override;

private:
    float base_cooldown = 3.0;
    float cur_cooldown = 3.0;
    bool isCoolingDown = false;

    PhysicsComponent* m_PhysComp;
};


#endif
