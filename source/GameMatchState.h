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
#include "PlayerManager.h"
#include "ObjectFactory.h"
#include "ScriptLoader.h"
//#include "CollisionManager.h"

#include "KeyBindingData.h"
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

    explicit GameMatchState(SDL_Renderer* renderer, std::shared_ptr<ScriptLoader> script_loader);
    ~GameMatchState();

    virtual void HandleEvents() override;
    virtual void Update() override;
    virtual void Render(SDL_Renderer* renderer) override;

private:

    void InitPhysics();

    std::vector<PlayerColorData> player_colors;
    PlayerColorData color;
    ArenaLayoutData arena;
    KeyBindingData keybindData;

    const int NumPlayers = 2;
    const int TeamSize = 3;

    SDL_Renderer* m_Renderer;
    std::shared_ptr<ScriptLoader> m_ScriptLoader;
    std::shared_ptr<EntityManager> m_EntityManager;
    std::shared_ptr<AssetManager> m_AssetManager;
    std::shared_ptr<ObjectFactory> m_ObjectFactory;
    std::shared_ptr<PlayerManager> m_PlayerManager;
    
    b2World* m_PhysicsWorld;
//    CollisionManager* m_CollisionManager;
    
    const float m_TimeStep;
    int m_VelocityIterations;
    int m_PositionIterations;
    int m_TicksLastFrame;

};


#endif
