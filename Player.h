#ifndef PLAYER_H
#define PLAYER_H

/*
The player class holds pointers to all of their balls and keeps track of the activeBall.
Will want to create a "AddPlayer" method to PhysicsState.  
Maybe have a static value in Player to help keep track of ID numbers?

The Player will also have a 'KeySet', which is a map of keybindings like
SDLK_Up: FwdMove,
SDLK_Down: BwdMove,
SDLK_Left: LeftTurn,
SDLK_Right: RightTurn
Then THESE actions will be sent to the Entity for handling.

Is pNum/PlayerNo necessary?

*/

#include "Entity.h"
//#include "Commands.h"
#include <vector>

class Command;

class Player
{
public:
    Player(int pNum, std::vector<Entity*> ents);
    Player(int pNum, std::vector<Entity*> ents, std::array<SDL_Keycode, 3> swap_keys);

    Player(int pNum, Entity* ent1, Entity* ent2, Entity* ent3);
    Player(int pNum, Entity* ent1, Entity* ent2, Entity* ent3, std::array<SDL_Keycode, 3> swap_keys);

    ~Player();

    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);

    Entity* GetActive() { return activeBall; }
    std::vector<Entity*> GetBalls() { return teamsBalls; }

    void SwapActiveBall(int newBall);

private:
    int PlayerNo;//Assigned upon Initialization.
    std::vector<Entity*> teamsBalls;
    Entity* activeBall;
    
    const std::vector<SDL_Keycode> ActionInputs = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT};
    const std::array<SDL_Keycode, 3> SwapKeys;

};

#endif