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
#include "SelectableComponent.h"

//#include "Commands.h"
#include <vector>

class Entity;
class Selector;
class Command;

class Player
{
public:
    Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys);

    ~Player();

    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);

    void AddEntity(Entity* newEnt) { teamsBalls.push_back(newEnt); }
    void AddBallToTeam(Entity* newEnt) { teamsBalls.push_back(newEnt); }

    Entity* GetActive() { return activeBall; }
    std::vector<Entity*> GetBalls() { return teamsBalls; }

    void SwapActiveBall(int new_ball);

    std::array<SDL_Keycode, 4> GetActionKeys() { return ActionKeys;}

    void RenderSelector(SDL_Renderer* renderer);
    void UpdateSelector();

    void InitializeActiveBall() {activeBall = teamsBalls[0]; }

private:

    std::vector<Entity*> teamsBalls;
    Entity* activeBall;
    
    const std::array<SDL_Keycode, 3> SwapKeys;
    const std::array<SDL_Keycode, 4> ActionKeys;
};

#endif