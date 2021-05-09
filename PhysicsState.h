#ifndef PHYSICS_STATE_H
#define PHYSICS_STATE_H

#include <memory>
#include <vector>

#include "App.h"
#include "State.h"
#include "EntityManager.h"
#include "Player.h"

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
    
    void InitWorld();
    void AddPlayer(Player* player) { players.push_back(player); }

    void AddPlayerBall(std::string name, b2Vec2 position, float radius, std::array<SDL_Keycode, 4> action_keys);

    SDL_Renderer* mnoptrrenderer;
    SDL_Surface* mnoptrsurface;
    b2World* world;
    EntityManager* manager;

    KeyInputComponent* mO1InputComp;
    KeyInputComponent* mO2InputComp;
    KeyInputComponent* mO3InputComp;

private:

    Entity* movingObj1 = nullptr;
    Entity* movingObj2 = nullptr;
    Entity* movingObj3 = nullptr;
    Entity* puckObj = nullptr;
    Entity* staticObj1 = nullptr;
    Entity* staticObj2 = nullptr;
    Entity* staticObj3 = nullptr;
    Entity* staticObj4 = nullptr;

    Player* P1;
    std::vector<Player*> players;

    float timeStep;
    int velocityIterations;
    int positionIterations;
    int ticksLastFrame;
};

#endif