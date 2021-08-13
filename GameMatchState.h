#ifndef GAME_MATCH_STATE_H
#define GAME_MATCH_STATE_H

#include <cassert>
#include <memory>
#include <vector>

#include "lua.hpp"

#include "Constants.h"
#include "AssetManager.h"
#include "App.h"
#include "State.h"
#include "EntityManager.h"
#include "Player.h"
#include "EntityFactory.h"
//#include "CollisionManager.h"


class KeyInputComponent;
class SelectableComponent;
class PhysicsComponent;
class GoalZoneComponent;
class SDLCircleComponent;
class SDLRectComponent;
class TextComponent;

struct KeyBindingData
{
    const std::array<SDL_Keycode, 3> P1SwapKeys = { SDLK_i, SDLK_o, SDLK_p };
    const std::array<SDL_Keycode, 4> P1ActionKeys = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };

    const std::array<SDL_Keycode, 3> P2SwapKeys = { SDLK_v, SDLK_b, SDLK_n };
    const std::array<SDL_Keycode, 4> P2ActionKeys = { SDLK_w, SDLK_s, SDLK_a, SDLK_d };
    
    const std::vector<std::array<SDL_Keycode, 3>> SwapKeys = {P1SwapKeys, P2SwapKeys};
    const std::vector<std::array<SDL_Keycode, 4>> ActionKeys = { P1ActionKeys, P2ActionKeys };
};

struct ArenaLayoutData
{
    //Lua imported variables.
    float WALL_THICKNESS;
    float WALL_BUFFER;
    float GOAL_WIDTH, GOAL_HEIGHT;
    std::vector<b2Vec2> P1StartingPositions;
    std::vector<b2Vec2> P2StartingPositions;

    //Derivative Variables from the Lua variables.
    //WallSizes
    b2Vec2 TopWallSize; 
    b2Vec2 BottomWallSize;
    b2Vec2 LeftWallSize;
    b2Vec2 RightWallSize;
    std::array<b2Vec2, 4> WallSizes;
    //GoalWallSizes
    b2Vec2 GoalTopWallSize;
    b2Vec2 GoalBotWallSize;
    b2Vec2 GoalSideWallSize;
    std::array<b2Vec2, 3> GoalWallSizes;
    b2Vec2 GoalSize; //Factor this out?
    std::vector<std::vector<b2Vec2>> StartingPositions;
    std::vector<b2Vec2> GoalPositions;
    std::vector<b2Vec2> ScoreDisplayPositions;

    b2Vec2 TopWallPos = {SCREEN_WIDTH/2, 30};
    b2Vec2 BottomWallPos = {SCREEN_WIDTH/2, SCREEN_HEIGHT - 30};
    b2Vec2 LeftWallPos = {30, SCREEN_HEIGHT/2};
    b2Vec2 RightWallPos = {SCREEN_WIDTH-30, SCREEN_HEIGHT/2};
    std::array<b2Vec2, 4> WallPositions = {TopWallPos, BottomWallPos, LeftWallPos, RightWallPos};

    b2Vec2 Goal1TopWallPos;
    b2Vec2 Goal1BotWallPos;
    b2Vec2 Goal1SideWallPos;
    std::array<b2Vec2, 3> Goal1WallPositions; 
    
    b2Vec2 Goal2TopWallPos;
    b2Vec2 Goal2BotWallPos;
    b2Vec2 Goal2SideWallPos;
    std::array<b2Vec2, 3> Goal2WallPositions; 
    
};


class GameMatchState : public State
{
public:

    explicit GameMatchState(SDL_Renderer* renderer);
    ~GameMatchState();

    void HandleEvents() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:

    bool CheckLua(lua_State* L, int r);

    void InitPhysics();

    void SetUpTwoPlayers();
    bool LoadArenaData(std::string arena_data_file);

    //Factory
    void SetUpPuck();
    void CreateBoundaries();
    void CreateGoalZones();
    void CreateGoalWalls();

    //Refactor this so the ints are x,y position, etc.
    void AddPlayerBall(std::shared_ptr<Player> player, int i, int j);




    ArenaLayoutData arena;
    KeyBindingData keybindData;

    const int NumPlayers = 2;
    const int TeamSize = 3;

    SDL_Renderer* m_Renderer;
    std::shared_ptr<EntityManager> m_EntityManager;
    std::shared_ptr<AssetManager> m_AssetManager;

    std::unique_ptr<EntityFactory> m_EntityFactory;
    
    b2World* m_PhysicsWorld;
//    CollisionManager* m_CollisionManager;
    
    std::vector<std::shared_ptr<Player>> m_Players;

    const float m_TimeStep;
    int m_VelocityIterations;
    int m_PositionIterations;
    int m_TicksLastFrame;

    float WALL_THICKNESS;
    float WALL_BUFFER;
    b2Vec2 GoalSize;
};


#endif
