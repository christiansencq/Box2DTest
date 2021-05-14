#ifndef PLAYER_H
#define PLAYER_H

/*
The player class holds pointers to all of their balls and keeps track of the activeBall.
Will want to create a "AddPlayer" method to PhysicsState.  
Maybe have a static value in Player to help keep track of ID numbers?

Is pNum/PlayerNo necessary?

*/

#include "SDL2/SDL.h"

#include "Entity.h"

//#include "Commands.h"
#include <vector>

class Entity;
class Selector;
class Command;

class Player
{
public:
    //Player(std::vector<Entity*> ents);
    //Player(std::vector<Entity*> ents, std::array<SDL_Keycode, 3> swap_keys);

    Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys);

    //Player(std::vector<Entity*> ents, std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys);
    
    //Player(Entity* ent1, Entity* ent2, Entity* ent3);
    //Player(Entity* ent1, Entity* ent2, Entity* ent3, std::array<SDL_Keycode, 3> swap_keys);

    ~Player();

    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);

    void AddEntity(Entity* newEnt) { teamsBalls.push_back(newEnt); }
    void AddBallToTeam(Entity* newEnt) { teamsBalls.push_back(newEnt); }
    //void AddTeam(std::vector<Entity*> ents);

    Entity* GetActive() { return activeBall; }
    std::vector<Entity*> GetBalls() { return teamsBalls; }

    void AddSelector();
    void SwapActiveBall(int new_ball);

    std::array<SDL_Keycode, 4> GetActionKeys() { return ActionKeys;}
    //Selector& GetSelector() { return *selector; }
    void RenderSelector(SDL_Renderer* renderer);
    void UpdateSelector();

private:

    std::vector<Entity*> teamsBalls;
    Entity* activeBall;
    
    const std::array<SDL_Keycode, 3> SwapKeys;
    const std::array<SDL_Keycode, 4> ActionKeys;

//    std::unique_ptr<Selector> selector;
    Selector* selector;
};

#endif