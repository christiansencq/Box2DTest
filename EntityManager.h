#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>

#include "Entity.h"
//class Entity;

#include "Player.h"
class Player;

class EntityManager 
{
public:
 //   EntityManager();

    void ClearData();
    
    //Methods that call analogous Entity methods.
    void Update();
    void Render(SDL_Renderer* renderer);
    void HandleInput(SDL_Event &event) {}
    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);

    //Entity Management and Access.
    Entity* AddEntity();
    Entity* AddEntity(b2Vec2 initPixelPos, b2Vec2 initPixelSize);
    Entity* AddEntity(b2Vec2 initPixelPos, float initPixelRadius);

    bool HasEntities() const { return entities.size() > 0; }
    std::vector<Entity*> GetEntities() const { return entities; }
    unsigned int GetEntityCount() const { return entities.size(); }

    void DestroyInactiveEntities();
    void AddPlayer(Player* player);

private:
    SDL_Renderer* renderer; //A shared pointer.
    //std::vector<std::shared_ptr<Entity>> entities;
    std::vector<Entity*> entities;
    std::vector<Player*> players;
    std::map<const std::string, Entity*> entityNameMap;
    b2World* physWorld;
};
#endif