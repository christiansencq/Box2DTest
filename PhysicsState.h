#ifndef PHYSICS_STATE_H
#define PHYSICS_STATE_H

#include <memory>
#include <vector>

#include "App.h"
#include "Constants.h"
#include "State.h"
#include "EntityManager.h"

class PhysicsComponent;

//Analogous to the Levels.
//https://github.com/borysn/SFML-Box2D-Simple-Level/blob/master/Level.cpp

class PhysicsState : public State
{
public:
    //PhysicsState(b2World* aWorld, SDL_Renderer* renderer)
    PhysicsState(SDL_Renderer* renderer, SDL_Surface* surface);
    ~PhysicsState();

    void init() override {}
    void HandleEvents() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;

    // void DrawAllPolys();
    // void DrawRect(b2Vec2* points, b2Vec2 center, float angle);
    // void DrawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1);
    // void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);
    SDL_Renderer* mnoptrrenderer;
    SDL_Surface* mnoptrsurface;
    b2World* world;
    EntityManager* manager;

private:

    //std::vector<PhysicsEntity> dynamicEntities;
    Entity* movingObj1 = nullptr;
    Entity* movingObj2 = nullptr;
    Entity* staticObj1 = nullptr;
    Entity* staticObj2 = nullptr;

    float timeStep;
    int velocityIterations;
    int positionIterations;
    int ticksLastFrame;
};

#endif