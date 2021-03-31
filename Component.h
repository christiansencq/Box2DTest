#pragma once

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

//#include "Entity.h"
class Entity;

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
    virtual void Render(SDL_Renderer* renderer) {}
    virtual void printType() const {}

    Entity* owner;
};
