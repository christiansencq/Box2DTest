#include "KeyInputComponent.h"


void KeyInputComponent::Initialize()
{
    physicsBody = owner->GetComponent<PhysicsComponent>();
}

void KeyInputComponent::HandleEvents(SDL_Event &event) 
{

}

void KeyInputComponent::HandleKeyPress(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_UP:
            physicsBody->SetThrusting(true);
            break;
        case SDLK_LEFT://May want to integrate these, make it so if one is pressed after the other, it takes over control, 
                       //but if both are held then one released, the other takes control.
            physicsBody->SetTurning(TurnDir::LEFT);
            break;
        case SDLK_RIGHT:
            physicsBody->SetTurning(TurnDir::RIGHT);
            break;
        case SDLK_DOWN:
            // DEBUG.
            std::cout << "Angle: " << physicsBody->GetPhysBody()->GetAngle() << "\n";
            std::cout << "WorldPos: " << physicsBody->GetPhysBody()->GetWorldCenter().x << ",  " << physicsBody->GetPhysBody()->GetWorldCenter().y << "\n";
            break;
        default:
            break;
    }
}

void KeyInputComponent::HandleKeyRelease(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_UP:
            physicsBody->SetThrusting(false);
            break;
        case SDLK_LEFT:
            physicsBody->SetTurning(TurnDir::NONE);
            break;
        case SDLK_RIGHT:
            physicsBody->SetTurning(TurnDir::NONE);
            break;
        default:
            break;
    }
}