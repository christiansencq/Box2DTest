#include "Player.h"

Player::Player(int pNum, std::vector<Entity*> ents)
 : PlayerNo(pNum), teamsBalls(ents), activeBall(teamsBalls[0]), SwapKeys (std::array<SDL_Keycode, 3> {SDLK_1, SDLK_2, SDLK_3})
{
    
}

Player::Player(int pNum, std::vector<Entity*> ents, std::array<SDL_Keycode, 3> swap_keys)
 : PlayerNo(pNum), teamsBalls(ents), activeBall(teamsBalls[0]), SwapKeys (swap_keys)
{
    
}

// Player::Player(int pNum, std::vector<Entity*> ents, std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys)
//  : PlayerNo(pNum), teamsBalls(ents), activeBall(teamsBalls[0]), SwapKeys (swap_keys), ActionKeys (action_keys)
// {

// }

Player::Player(int pNum, Entity* ent1, Entity* ent2, Entity* ent3)
 : PlayerNo(pNum), SwapKeys (std::array<SDL_Keycode, 3> {SDLK_1, SDLK_2, SDLK_3})
{
    teamsBalls = { ent1, ent2, ent3};
    activeBall = teamsBalls[0];
}

Player::Player(int pNum, Entity* ent1, Entity* ent2, Entity* ent3, std::array<SDL_Keycode, 3> swap_keys)
 : SwapKeys(swap_keys)
{
    teamsBalls = { ent1, ent2, ent3};
    activeBall = teamsBalls[0];
}

void Player::HandleKeyPress(SDL_Keycode key) 
{
    if (key == SwapKeys[0])
    {
        SwapActiveBall(0);
    }
    else if (key == SwapKeys[1])
    {
        SwapActiveBall(1);
    }
    else if (key == SwapKeys[2])
    {
        SwapActiveBall(2);
    }
    else
    {
        activeBall->HandleKeyPress(key);
    }
}

void Player::HandleKeyRelease(SDL_Keycode key)
{
    activeBall->HandleKeyRelease(key);     
}

void Player::SwapActiveBall(int newBall) 
{
    std::cout << "Old activeBall: " << activeBall << " -  New activeBall: " << teamsBalls[newBall] << "\n";
    activeBall = teamsBalls[newBall];
}
