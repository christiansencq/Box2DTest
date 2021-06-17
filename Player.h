#ifndef PLAYER_H
#define PLAYER_H

/*

The player class holds pointers to all of their balls and keeps track of the activeBall.
Will want to create a "AddPlayer" method to PhysicsState.  
Maybe have a static value in Player to help keep track of ID numbers?
*/
#include <vector>

#include "SDL2/SDL.h"

#include "Entity.h"

class Selector;
class Command;

class Player
{
public:
    Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys, Entity* score_display);
    ~Player();

    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);

    void AddBallToTeam(Entity* new_entity) { m_TeamsBalls.push_back(new_entity); }

    Entity* GetActive() { return m_ActiveBall; }
    std::vector<Entity*> GetBalls() { return m_TeamsBalls; }

    void SwapActiveBall(int new_ball);

    std::array<SDL_Keycode, 4> GetActionKeys() { return m_ActionKeys;}

    void RenderSelector(SDL_Renderer* renderer);
    void UpdateSelector();

    void InitializeActiveBall() {m_ActiveBall = m_TeamsBalls[0]; }

    void IncrementScore(int num);
    int GetScore() { return m_Score; }
private:

    SDL_Renderer* m_Renderer;
    std::vector<Entity*> m_TeamsBalls;
    Entity* m_ActiveBall;
    Entity* m_ScoreDisplay;    
    const std::array<SDL_Keycode, 3> m_SwapKeys;
    const std::array<SDL_Keycode, 4> m_ActionKeys;

    int m_Score;
};

#endif
