#pragma once

#include <memory>
#include <vector>

#include "App.h"
#include "Constants.h"
#include "State.h"
#include "Entity.h"
#include "EntityManager.h"

//Analogous to the Levels.
//https://github.com/borysn/SFML-Box2D-Simple-Level/blob/master/Level.cpp

class PhysicsState : public State
{
public:
    //PhysicsState(b2World* aWorld, SDL_Renderer* renderer)
    PhysicsState(SDL_Renderer* renderer);
    ~PhysicsState();

    void init() override {}
    void HandleEvents() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:
    SDL_Renderer* mnoptrrenderer;
    b2World* world;
    EntityManager* manager;

    //std::vector<PhysicsEntity> dynamicEntities;
    Entity* movingObject;
    Entity* staticObject;

    float timeStep;
    int velocityIterations;
    int positionIterations;
};