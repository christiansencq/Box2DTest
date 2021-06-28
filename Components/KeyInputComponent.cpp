#include "KeyInputComponent.h"
#include "PhysicsComponent.h"

KeyInputComponent::KeyInputComponent(std::array<SDL_Keycode, 4> action_keys)
 : m_ActionKeys(action_keys)
{
}

KeyInputComponent::~KeyInputComponent()
{
    //Need to go through and delete all of the m_Commands.
    for (auto cmd : m_Commands)
    {
        delete cmd;
    }

}

void KeyInputComponent::Initialize()
{

}

void KeyInputComponent::HandleEvents(SDL_Event &event) 
{

}

void KeyInputComponent::HandleKeyPress(SDL_Keycode key)
{
    //Can't use a switch statement, since the values in m_ActionKeys aren't constexprs.
    if (key == m_ActionKeys[0])
    {
        m_ActionMap[Actions::FORWARD]->executePress();
    }
    else if (key == m_ActionKeys[1])
    {
        m_ActionMap[Actions::BACKWARD]->executePress();
    }
    else if (key == m_ActionKeys[2])
    {
        m_ActionMap[Actions::LEFT]->executePress();
    }
    else if (key == m_ActionKeys[3])
    {
        m_ActionMap[Actions::RIGHT]->executePress();
    }
}

void KeyInputComponent::HandleKeyRelease(SDL_Keycode key)
{
    if (key == m_ActionKeys[0])
    {
        m_ActionMap[Actions::FORWARD]->executeRelease();
    }
    else if (key == m_ActionKeys[1])
    {
        //DownRelease();
    }
    else if (key == m_ActionKeys[2])
    {
        m_ActionMap[Actions::LEFT]->executeRelease();
    }
    else if (key == m_ActionKeys[3])
    {
        m_ActionMap[Actions::RIGHT]->executeRelease();
    }
}
