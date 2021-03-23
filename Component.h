#pragma once

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "Entity.h"

class Entity;

class Component
{
public:
    Entity* owner;
    Component() {}
    virtual ~Component() {}
    virtual void Initialize() {}
    virtual void Update() {}
    virtual void Render(SDL_Renderer* renderer) {}
    virtual void printType() const {}
};
