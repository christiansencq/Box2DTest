#ifndef ACTION_COMPONENT_H
#define ACTION_COMPONENT_H

#include "PhysicsComponent.h"

class Command
{
public:
    Command() {}

    virtual void execute() {}

    bool IsPressed;

    Entity* owner;

    PhysicsComponent* physicsBody;

};

//This holds the actions for a Forward, Backward, Left, Right key press.
//Could rename to 'ActionSet' or similar.   For now, can be an aggregate.

class ActionComponent : public Component
{
public:
    ActionComponent() {}
    ~ActionComponent() {}

    void Initialize() override;

    // void ForwardPress();
    // void ForwardRelease();
    
    // void BackwardPress();
    // void BackwardRelease();

    // void LeftPress();
    // void LeftRelease();

    // void RightPress();
    // void RightRelease();

    void printType() const override {}

    Entity* owner;

private:
    PhysicsComponent* physicsComp;

    Command* ForwardCommand;
    Command* BackwardCommand;
    Command* LeftCommand;
    Command* RightCommand;

    bool ForwardIsPressed;
    bool BackwardIsPressed;
    bool LeftIsPressed;
    bool RightIsPressed;
};

#endif


