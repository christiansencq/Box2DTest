#pragma once

#include <memory>

#include "State.h"
#include "App.h"
#include "PhysicsEntity.h"
//Analogous to the Levels.
//https://github.com/borysn/SFML-Box2D-Simple-Level/blob/master/Level.cpp

class PhysicsState : public State
{
public:
    //PhysicsState(b2World* aWorld, SDL_Renderer* renderer)
    PhysicsState(SDL_Renderer* renderer);
    ~PhysicsState();

    void init() override {}
    void handleEvents() override;
    void update() override;
    void render(SDL_Renderer* renderer) override;


private:
    SDL_Renderer* mnoptrrenderer;
    
    b2World* world;
    
    //aBody borderPlatforms[4];
    PhysicsEntity* mGroundBody;
    PhysicsEntity* mMovingBody;

    float timeStep;
    int velocityIterations;
    int positionIterations;
};