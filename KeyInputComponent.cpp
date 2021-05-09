#include "KeyInputComponent.h"


KeyInputComponent::KeyInputComponent(std::array<SDL_Keycode, 4> action_keys)
 : actionKeys(action_keys)
{
}

KeyInputComponent::~KeyInputComponent()
{
    //Need to go through and delete all of the Commands.
    for (auto cmd : commands)
    {
        delete cmd;
    }

}

void KeyInputComponent::Initialize()
{
    physicsComp = owner->GetComponent<PhysicsComponent>();
}

void KeyInputComponent::HandleEvents(SDL_Event &event) 
{

}

void KeyInputComponent::HandleKeyPress(SDL_Keycode key)
{
    //Can't use a switch statement, since the values in actionKeys aren't constexprs.

    if (key == actionKeys[0])
    {
        ActionMap[Actions::FORWARD]->executePress();
    }
    else if (key == actionKeys[1])
    {
        ActionMap[Actions::BACKWARD]->executePress();
    }
    else if (key == actionKeys[2])
    {
        ActionMap[Actions::LEFT]->executePress();
    }
    else if (key == actionKeys[3])
    {
        ActionMap[Actions::RIGHT]->executePress();
    }
}

void KeyInputComponent::HandleKeyRelease(SDL_Keycode key)
{
    if (key == actionKeys[0])
    {
        ActionMap[Actions::FORWARD]->executeRelease();
    }
    else if (key == actionKeys[1])
    {
        //DownRelease();
    }
    else if (key == actionKeys[2])
    {
        ActionMap[Actions::LEFT]->executeRelease();
    }
    else if (key == actionKeys[3])
    {
        ActionMap[Actions::RIGHT]->executeRelease();
    }
}