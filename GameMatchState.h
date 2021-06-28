#ifndef GAME_MATCH_STATE_H
#define GAME_MATCH_STATE_H

#include <memory>
#include <vector>

#include "Constants.h"
#include "AssetManager.h"
#include "App.h"
#include "State.h"
#include "EntityManager.h"
#include "Player.h"
/*
#include "Components/KeyInputComponent.h"
#include "Components/SelectableComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/GoalZoneComponent.h"
#include "Components/SDLCircleComponent.h"
#include "Components/SDLRectComponent.h"
#include "Components/TextComponent.h"
*/
class KeyInputComponent;
class SelectableComponent;
class PhysicsComponent;
class GoalZoneComponent;
class SDLCircleComponent;
class SDLRectComponent;
class TextComponent;

class GameMatchState : public State
{
public:

    void InitWorld();
    void AddPlayer(std::shared_ptr<Player> player) { m_Players.push_back(player); }
    void AddPlayerBall(Entity* entity, std::shared_ptr<Player> player);
//    void SetUpPlayers(std::vector<std::vector<Entity*>> PlayerTeams);
    void SetUpPlayers();
    void InitPlayers(int num_players);
    void CreateBoundaries();
    void CreateGoalZones();

    //Single Argument Constructor Without Explicit is a Converting Constructor
    explicit GameMatchState(SDL_Renderer* renderer);
    ~GameMatchState();

    void Reset();
    void ResetPositions();

    void HandleEvents() override;
    void Update() override;

    void Render(SDL_Renderer* renderer) override;

private:

    const std::vector<b2Vec2> P1StartingPositions = {b2Vec2{350, 640}, b2Vec2{350, 480}, b2Vec2{350, 320}};
    const std::vector<b2Vec2> P2StartingPositions = {b2Vec2{750, 640}, b2Vec2{750, 480}, b2Vec2{750, 320}};
    const std::array<SDL_Keycode, 3> P1SwapKeys = { SDLK_i, SDLK_o, SDLK_p };
    const std::array<SDL_Keycode, 4> P1ActionKeys = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
    const std::array<SDL_Keycode, 3> P2SwapKeys = { SDLK_v, SDLK_b, SDLK_n };
    const std::array<SDL_Keycode, 4> P2ActionKeys = { SDLK_w, SDLK_s, SDLK_a, SDLK_d };

    std::unique_ptr<EntityManager> m_Manager;
    AssetManager* m_AssetManager;
    SDL_Renderer* m_Renderer;
    b2World* m_World;
    TTF_Font* m_ScoreFont;
    
    Entity* movingObj1 = nullptr;
    Entity* movingObj2 = nullptr;
    Entity* movingObj3 = nullptr;
    Entity* puckObj = nullptr;
    //Walls
    Entity* staticObj1 = nullptr;
    Entity* staticObj2 = nullptr;
    Entity* staticObj3 = nullptr;
    Entity* staticObj4 = nullptr;
    
    Entity* goalZone = nullptr;

    Entity* m_P1ScoreDisplayUI = nullptr;
    Entity* m_P2ScoreDisplayUI = nullptr;
    std::vector<Entity*> m_ScoreDisplays;

    std::shared_ptr<Player> m_P1;
    std::shared_ptr<Player> m_P2;
    //TODO see about removing this... or rather, the individual player pointers above.
    std::vector<std::shared_ptr<Player>> m_Players;

    bool m_GoalMade = false;
    float m_TimeStep;
    int m_VelocityIterations;
    int m_PositionIterations;
    int m_TicksLastFrame;
};

#endif
