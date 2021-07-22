#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <array>

#include "Box2D/Box2D.h"
#include "SDL2/SDL.h"

class Entity;
class Selector;
class Command;

class Player
{
public:

    Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys);
    Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys, Entity* score_display);
    Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys, Entity* score_display, std::vector<b2Vec2> starting_pos);
    ~Player();

    void ResetPositions();
    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);
    void AddBallToTeam(Entity* new_entity) { m_TeamsBalls.push_back(new_entity); }
    Entity* GetActive() { return m_ActiveBall; }
    std::vector<Entity*> GetBalls() { return m_TeamsBalls; }
    void SwapActiveBall(int new_ball);
    std::array<SDL_Keycode, 4> GetActionKeys() { return m_ActionKeys;}

    //Selector Indicator
    void RenderSelector(SDL_Renderer* renderer);
    void UpdateSelector();

    void AddStartingPositions(std::vector<b2Vec2> start_pos) {m_StartingPositions = start_pos; }
    //Scoring:
    void AddScoreDisplay(Entity* score_disp);
    void IncrementScore(int num);
    int GetScore() { return m_Score; }

private:
    
    std::vector<b2Vec2> m_StartingPositions;
//    SDL_Renderer* m_Renderer;
    std::vector<Entity*> m_TeamsBalls;
    Entity* m_ActiveBall;
    Entity* m_ScoreDisplay;    
    const std::array<SDL_Keycode, 3> m_SwapKeys;
    const std::array<SDL_Keycode, 4> m_ActionKeys;
    int m_Score = 0;
};

#endif
