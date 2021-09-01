#ifndef GAME_MATCH_STATE_H
#define GAME_MATCH_STATE_H

#include <cassert> 
#include <memory>
#include <vector>

#include "lua.hpp"

#include "Data/Constants.h"
#include "Data/Colors.h"

#include "AssetManager.h"
#include "App.h"
#include "State.h"
#include "EntityManager.h"
#include "PlayerManager.h"
#include "ObjectFactory.h"
#include "ScriptLoader.h" 

class KeyInputComponent;
class SelectableComponent;
class PhysicsComponent;
class GoalZoneComponent;
class SDLCircleComponent;
class SDLRectComponent;
class TextComponent;

///The state in which the Hockey Match itself is played.
class GameMatchState : public State
{
public:

    explicit GameMatchState(SDL_Renderer* renderer, ScriptLoader& script_loader);
    ~GameMatchState();

    virtual void HandleEvents() override;
    virtual void Update() override;
    virtual void Render(SDL_Renderer* renderer) override;


private:

    bool paused = false;
    b2World* InitPhysics();

    std::vector<PlayerColorData> player_colors;
    PlayerColorData color;
    ArenaLayoutData arena;
    KeyBindingData keybindData;

    const int NumPlayers = 2;
    const int TeamSize = 3;

    SDL_Renderer* m_Renderer;
    ScriptLoader& m_ScriptLoader;

    EntityManager m_EntityManager;

    AssetManager m_AssetManager;
    b2World* m_PhysicsWorld;
    ObjectFactory m_ObjectFactory;
    PlayerManager m_PlayerManager;
    
//    CollisionManager* m_CollisionManager;
    
    const float m_TimeStep;
    const int m_VelocityIterations;
    const int m_PositionIterations;
    int m_TicksLastFrame;

};


#endif
