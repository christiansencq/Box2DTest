
#include "PhysicsComponent.h"

class Command
{
public:
    virtual void execute() {}

    bool IsPressed;

    Entity* owner;

    PhysicsComponent* physicsBody;

};

class ForwardCommand : public Command
{
public:
    void execute() override
    {
        physicsBody->
    }


};

class BackwardCommand : public Command
{
public:
    void execute() override
    {

    }


};