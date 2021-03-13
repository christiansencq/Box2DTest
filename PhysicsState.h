#pragma once

#include <memory>

#include "State.h"
#include "App.h"
#include "DynBody.h"
#include "StatBody.h"

class PhysicsState : public State
{
public:
    PhysicsState(SDL_Renderer* renderer);
    ~PhysicsState();

    void init() override {}
    void handleEvents() override;
    void update() override;
    void render(SDL_Renderer* renderer) override;

    b2Body* createStaticBody(b2World& world);
    b2Body* createDynamicBody(b2World& world);

private:
    SDL_Renderer* mnoptrrenderer;

    b2Vec2 gravity;

    b2World* mWorld;

    b2Body* mGroundBody;
    b2Body* mMovingBody;
};