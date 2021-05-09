#include "KeyInputComponent.h"


KeyInputComponent::KeyInputComponent(std::array<SDL_Keycode, 4> action_keys)
{
    actionKeys = action_keys;
}

KeyInputComponent::~KeyInputComponent()
{
    delete ActionMap[Actions::FORWARD];
    delete ActionMap[Actions::LEFT];
    delete ActionMap[Actions::RIGHT];
}

void KeyInputComponent::Initialize()
{
    physicsComp = owner->GetComponent<PhysicsComponent>();
    //Get COMMANDS instead, the commands will access the components they need.

    ActionMap[Actions::FORWARD] = new ForwardThrustCommand();
    ActionMap[Actions::LEFT] = new LeftTurnCommand();
    ActionMap[Actions::RIGHT] = new RightTurnCommand();
}

void KeyInputComponent::HandleEvents(SDL_Event &event) 
{

}

void KeyInputComponent::HandleKeyPress(SDL_Keycode key)
{
    // switch (key)
    // {
    //     case actionKeys[0]:
    //     //case SDLK_UP:
    //         ForwardPress();
    //         break;
    //     case SDLK_LEFT://May want to integrate these, make it so if one is pressed after the other, it takes over control, 
    //                    //but if both are held then one released, the other takes control.
    //         LeftPress();
    //         break;
    //     case SDLK_RIGHT:
    //         RightPress();
    //         break;
    //     case SDLK_DOWN:
    //         break;
    //     default:
    //         break;
    // }

    if (key == actionKeys[0])
    {
        ActionMap[Actions::FORWARD]->executePress();
    }
    else if (key == actionKeys[1])
    {
        //DownPress();
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
    // switch (key)
    // {
    //     case SDLK_UP:
    //         ForwardRelease();
    //         break;
    //     case SDLK_LEFT:
    //         LeftRelease();
    //         break;
    //     case SDLK_RIGHT:
    //         RightRelease();
    //         break;
    //     case SDLK_DOWN:
    //         break;
    //     default:
    //         break;
    // }

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

//Commands
void KeyInputComponent::ForwardPress()
{
    physicsComp->SetThrusting(true);
}

void KeyInputComponent::ForwardRelease()
{
    physicsComp->SetThrusting(false);
}

void KeyInputComponent::BackwardPress()
{

}

void KeyInputComponent::BackwardRelease()
{

}

void KeyInputComponent::LeftPress()
{
    physicsComp->SetTurning(TurnDir::LEFT);
}

void KeyInputComponent::LeftRelease()
{
    physicsComp->SetTurning(TurnDir::NONE);
}

void KeyInputComponent::RightPress() 
{
    physicsComp->SetTurning(TurnDir::RIGHT);
}

void KeyInputComponent::RightRelease() 
{
    physicsComp->SetTurning(TurnDir::NONE);
}