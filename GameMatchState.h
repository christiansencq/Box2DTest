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
#include "CollisionManager.h"

class KeyInputComponent;
class SelectableComponent;
class PhysicsComponent;
class GoalZoneComponent;
class SDLCircleComponent;
class SDLRectComponent;
class TextComponent;

struct KeyBindingData
{
    std::array<SDL_Keycode, 3> P1SwapKeys = { SDLK_i, SDLK_o, SDLK_p };
    std::array<SDL_Keycode, 4> P1ActionKeys = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
    std::array<SDL_Keycode, 3> P2SwapKeys = { SDLK_v, SDLK_b, SDLK_n };
    std::array<SDL_Keycode, 4> P2ActionKeys = { SDLK_w, SDLK_s, SDLK_a, SDLK_d };
    std::vector<std::array<SDL_Keycode, 3>> SwapKeys = {P1SwapKeys, P2SwapKeys};
    std::vector<std::array<SDL_Keycode, 4>> ActionKeys = { P1ActionKeys, P2ActionKeys };
};

struct ArenaLayoutData
{
    const float WALL_THICKNESS = 10.f;
    const float WALL_BUFFER = 50.f;
    const b2Vec2 GoalSize = {250, 500};

    //Data/Constants
    const std::vector<b2Vec2> P1StartingPositions = {b2Vec2{450, 640}, b2Vec2{450, 480}, b2Vec2{450, 320}};
    const std::vector<b2Vec2> P2StartingPositions = {b2Vec2{1150, 640}, b2Vec2{1150, 480}, b2Vec2{1150, 320}};
    const std::vector<std::vector<b2Vec2>> StartingPositions = {P1StartingPositions, P2StartingPositions};

    const std::array<b2Vec2, 2> ScoreDisplayPositions = {b2Vec2{150, 50}, b2Vec2{800, 50}};

    const b2Vec2 TopWallPos = {SCREEN_WIDTH/2, 30};
    const b2Vec2 BottomWallPos = {SCREEN_WIDTH/2, SCREEN_HEIGHT - 30};
    const b2Vec2 LeftWallPos = {30, SCREEN_HEIGHT/2};
    const b2Vec2 RightWallPos = {SCREEN_WIDTH-30, SCREEN_HEIGHT/2};
    const std::array<b2Vec2, 4> WallPoses = {TopWallPos, BottomWallPos, LeftWallPos, RightWallPos};

    std::array<b2Vec2, 2> GoalPositions = {b2Vec2{1400, 450}, b2Vec2{200, 450}};

    const b2Vec2 Goal1TopWallPos = { GoalPositions[0].x, GoalPositions[0].y - GoalSize.y/2 };
    const b2Vec2 Goal1BotWallPos = { GoalPositions[0].x, GoalPositions[0].y + GoalSize.y/2 };
    const b2Vec2 Goal1SideWallPos = { GoalPositions[0].x + GoalSize.x/2, GoalPositions[0].y };
    const std::array<b2Vec2, 3> Goal1WallPositions = {Goal1TopWallPos, Goal1BotWallPos, Goal1SideWallPos};
    
    const b2Vec2 Goal2TopWallPos = { GoalPositions[1].x, GoalPositions[1].y - GoalSize.y/2 };
    const b2Vec2 Goal2BotWallPos = { GoalPositions[1].x, GoalPositions[1].y + GoalSize.y/2 };
    const b2Vec2 Goal2SideWallPos = { GoalPositions[1].x - GoalSize.x/2, GoalPositions[1].y };
    const std::array<b2Vec2, 3> Goal2WallPositions = {Goal2TopWallPos, Goal2BotWallPos, Goal2SideWallPos};

    //Sizes
    const b2Vec2 TopWallSize = {SCREEN_WIDTH-70, WALL_THICKNESS};
    const b2Vec2 BottomWallSize = {SCREEN_WIDTH-70, WALL_THICKNESS};
    const b2Vec2 LeftWallSize = {WALL_THICKNESS, SCREEN_HEIGHT-WALL_BUFFER};
    const b2Vec2 RightWallSize = {WALL_THICKNESS, SCREEN_HEIGHT-WALL_BUFFER};
    const std::array<b2Vec2, 4> WallSizes = {TopWallSize, BottomWallSize, LeftWallSize, RightWallSize};
    
    const b2Vec2 GoalTopWallSize = { GoalSize.x + (2 * WALL_THICKNESS), WALL_THICKNESS };
    const b2Vec2 GoalBotWallSize = { GoalSize.x + (2 * WALL_THICKNESS), WALL_THICKNESS };
    const b2Vec2 GoalSideWallSize = { WALL_THICKNESS, GoalSize.y };
    const std::array<b2Vec2, 3> GoalWallSizes = { GoalTopWallSize, GoalBotWallSize, GoalSideWallSize };
};

class GameMatchState : public State
{
public:

    void InitPhysics();
    void SetUpTwoPlayers();
    void SetUpPuck();
    void CreateBoundaries2();
    void CreateGoalZones();
    void CreateGoalWalls();
    void AddPlayerBall(std::shared_ptr<Player> player, int i, int j);

    explicit GameMatchState(SDL_Renderer* renderer);
    ~GameMatchState();

    void HandleEvents() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:

    ArenaLayoutData arenaData;
    KeyBindingData keybindData;

    const int NumPlayers = 2;
    const int TeamSize = 3;

    SDL_Renderer* m_Renderer;
    std::unique_ptr<EntityManager> m_EntityManager;
    AssetManager* m_AssetManager;
    b2World* m_PhysicsWorld;
    CollisionManager* m_CollisionManager;
    
    std::vector<std::shared_ptr<Player>> m_Players;

    const float m_TimeStep;
    int m_VelocityIterations;
    int m_PositionIterations;
    int m_TicksLastFrame;

};


#endif
