#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "Component.h"
#include "Entity.h"

//class Entity;

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(float w, float h, float x, float y, b2World* world, bool dynamic = false);
    PhysicsComponent(b2Vec2 physSize, b2Vec2 physPos, b2World* world, bool dynamic = false);
    ~PhysicsComponent();
    void Initialize();
    void HandleEvents(SDL_Event &event) {}
    void HandleKeyPress(const SDL_Keycode key);
    void HandleKeyRelease(const SDL_Keycode key);
    void Update();
    void Render(SDL_Renderer* renderer);
    void printType() const;

    b2Body* GetPhysBody() { return physBody; }

    Entity* owner;

private:
//    Entity* owner;

    float mWidth;
    float mHeight;
    float mPhysX;
    float mPhysY;

    float density;
    float friction;
    float angle;
    bool isThrusting;

    b2Body* physBody;
    b2World* physWorld;

//    std::unique_ptr<b2Body> physBody;
//    std::shared_ptr<b2World> physWorld;

    bool isDynamic;
    const std::string type = "PhysicsComponent";
};

#endif