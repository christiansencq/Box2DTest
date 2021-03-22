#pragma once

#include "SDL2/SDL.h"

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
    virtual void Update(b2World* world) {}
    virtual void Render(SDL_Renderer* renderer) {}
    virtual void printType() const {}
};
