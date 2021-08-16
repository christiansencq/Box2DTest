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

#include "KeybindData.h"
#include "ArenaLayout.h"

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

    explicit GameMatchState(SDL_Renderer* renderer);
    ~GameMatchState();

    void HandleEvents() override;
    void Update() override;
    void Render(SDL_Renderer* renderer) override;

private:

    bool CheckLua(lua_State* L, int r);

    void LuaGetTableFromKey(lua_State* L, const char* key);
    float LuaIndexToFloat(lua_State* L, int index);
    float LuaKeyToFloat(lua_State* L, const char* lua_var_name);
    b2Vec2 LuaKeyTob2Vec(lua_State* L, const char* key);

    void InitPhysics();

    void SetUpTwoPlayers();
    bool LoadArenaData(std::string arena_data_file);


    // void AddPlayerBalls(std::shared_ptr<Player> player, int player_number, int team_size);
    void AddPlayerBalls(std::shared_ptr<Player> player, int team_size);


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
