#ifndef COMMANDS_H
#define COMMANDS_H

#include "Command.h"
//#include "KeyInputComponent.h"

class KeyInputComponent;

class ForwardThrustCommand : public Command
{
public:
    ForwardThrustCommand();
    virtual void Initialize();
    virtual void executePress();
    virtual void executeRelease();

    KeyInputComponent* owningComponent;
};


class LeftTurnCommand : public Command
{
public:
    LeftTurnCommand();
    virtual void Initialize();
    virtual void executePress();
    virtual void executeRelease();

    KeyInputComponent* owningComponent;

};

class RightTurnCommand : public Command
{
public:
    RightTurnCommand();
    virtual void Initialize();
    virtual void executePress();
    virtual void executeRelease();

    KeyInputComponent* owningComponent;
};


#endif