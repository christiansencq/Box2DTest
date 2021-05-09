#ifndef COMMAND_H
#define COMMAND_H

//#include "KeyInputComponent.h"

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

};

#endif