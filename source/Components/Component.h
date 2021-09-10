#ifndef COMPONENT_H
#define COMPONENT_H

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

class Entity;

/*
Provide further breakdowns of components to like renderers, input handlers, etc?
Certainly want Entities to only try to call methods of components WITH a relevant method (not an empty one)

These virtual functions should be shared by ALL components!  (Maybe I just need: Initialize, printType)
*/

class Component
{
public:
    Component() {}
    virtual ~Component() {}
    virtual void Initialize() {}
    virtual void HandleEvents(SDL_Event &event) {}
    virtual void HandleKeyPress(SDL_Keycode key) {}
    virtual void HandleKeyRelease(SDL_Keycode key) {}
    virtual void Update() {}
    virtual void Render() {}
    virtual void printType() const {}

    //virtual Entity* GetOwner() { return owner; }

//    Entity* owner;
};

#endif
