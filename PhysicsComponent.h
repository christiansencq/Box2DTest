#pragma once

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "Component.h"

class Entity;

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(float w, float h, float x, float y, b2World* world, bool dynamic = false);
    ~PhysicsComponent();
    void Initialize();
    void HandleEvents(SDL_Event &event) {}
    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);
    void Update();
    void Render(SDL_Renderer* renderer);
    void printType() const;

    b2Body* GetPhysBody() { return physBody; }

    Entity* GetOwner() {return owner; }

    Entity* owner;

private:
    float mWidth;
    float mHeight;

    float density;
    float friction;

    b2Body* physBody;
    b2World* physWorld;

//    std::unique_ptr<b2Body> physBody;
//    std::shared_ptr<b2World> physWorld;

    bool isDynamic;
    const std::string type = "PhysicsComponent";
};