#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <cassert>
#include <memory>
#include <vector>

#include "Constants.h"
#include "EntityManager.h"
#include "Player.h"
#include "ArenaLayout.h"
// #include "KeyBindingData.h"
#include "Components/KeyInputComponent.h"


class KeyInputComponent;
class SelectableComponent;
class PhysicsComponent;
class GoalZoneComponent;
class SDLCircleComponent;
class SDLRectComponent;
class TextComponent;

class ObjectFactory
{
public:
    ObjectFactory(SDL_Renderer* renderer, ArenaLayoutData& arena, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<EntityManager> entityManager, b2World* physWorld);
    ObjectFactory(SDL_Renderer* renderer, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<EntityManager> entityManager, b2World* physWorld);

    void CreateGoalWalls(std::vector<b2Vec2> wallPositions, std::vector<b2Vec2> wallSizes);

    Entity* CreateGoalZone(std::shared_ptr<Player> player, b2Vec2 position, b2Vec2 size);
    Entity* CreateScoreDisplay(std::shared_ptr<Player> player, b2Vec2 position, b2Vec2 size);

    void CreateOuterWalls(std::vector<b2Vec2> positions, std::vector<b2Vec2> sizes);
    void CreateTeamForPlayer(std::shared_ptr<Player> player, int team_size);
    
    Entity* CreatePlayerBall(std::shared_ptr<Player> player, b2Vec2 startPos, SDL_Color sel_color);

    // Entity* CreatePlayerBall(std::shared_ptr<Player> player, b2Vec2 startPos);
    Entity* CreatePuck(b2Vec2 startPos);

    ArenaLayoutData& GetArena() { return arena; }

private:

    SDL_Renderer* m_Renderer;
    ArenaLayoutData& arena;
    std::shared_ptr<AssetManager> m_AssetManager;
    std::shared_ptr<EntityManager> m_EntityManager;
    b2World* m_PhysicsWorld;

};

#endif
