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

    
    Player(int id_num, std::vector<std::vector<SDL_Keycode>> keybind);
    ~Player();

    void ResetPositions();

    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);

    void AddBallToTeam(Entity* new_entity);
    void AddStartingPositions(const std::vector<b2Vec2>& start_pos) { m_StartingPositions = start_pos; }

    void SwapActiveBall(int new_ball);

    Entity* GetActive() { return m_ActiveBall; }
    std::vector<Entity*> GetBalls() { return m_TeamsBalls; }
    std::vector<SDL_Keycode> GetActionKeys() { return m_ActionKeys;}
    
    //Score
    void AddScoreDisplay(Entity* score_disp) { m_ScoreDisplay = score_disp; }
    int GetScore() const { return m_Score; }
    void SetScore(int score) { m_Score = score; }
    void IncrementScore();

    //Selector Indicator
    void RenderSelector(SDL_Renderer* renderer);
    void UpdateSelector();

    //Scoring:
    int GetPlayerID() const { return id_number; }

private:
    const int id_number;

    std::vector<b2Vec2> m_StartingPositions;
    std::vector<Entity*> m_TeamsBalls;

    Entity* m_ActiveBall;
    Entity* m_ScoreDisplay;

    const std::vector<SDL_Keycode> m_SwapKeys;
    const std::vector<SDL_Keycode> m_ActionKeys;

    int m_Score;
};


#endif
