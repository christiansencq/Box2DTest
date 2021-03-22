#pragma once

#include <iostream>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "Component.h"

class Entity;

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(float w, float h, float x, float y, b2World* world, bool dynamic = false);
    ~PhysicsComponent();
    void Initialize() override;
    void Update(b2World* world) override;
    void Render(SDL_Renderer* renderer) override;
    void printType() const override;

    b2Body* GetPhysBody() { return physBody; }

private:
    float mWidth;
    float mHeight;

    float density;
    float friction;

    b2Body* physBody;
    b2World* physWorld;

    bool isDynamic;
    std::string type = "PhysicsComponent";
};