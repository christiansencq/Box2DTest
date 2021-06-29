#ifndef COMMANDS_H
#define COMMANDS_H

#include "../Constants.h"

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

    KeyInputComponent* owningComponent;

private:

};

class ForwardThrustCommand : public Command
{
//Add in a vector to thrust upon?


public:
    ForwardThrustCommand();
    virtual void Initialize() override;
    virtual void executePress() override;
    virtual void executeRelease() override;

//    KeyInputComponent* owningComponent;

private:


};

class BackwardThrustCommand : public Command
{
public:
    BackwardThrustCommand();
    virtual void Initialize();
    virtual void executePress();
    virtual void executeRelease();

//    KeyInputComponent* owningComponent;

private:

};

class LeftTurnCommand : public Command
{
public:
    LeftTurnCommand();
    virtual void Initialize();
    virtual void executePress();
    virtual void executeRelease();

//    KeyInputComponent* owningComponent;

private:


};

class RightTurnCommand : public Command
{
public:
    RightTurnCommand();
    virtual void Initialize();
    virtual void executePress();
    virtual void executeRelease();

    KeyInputComponent* owningComponent;

private:


};


#endif