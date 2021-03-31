#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
//class Entity;

class EntityManager 
{
public:
 //   EntityManager();

    void ClearData();
    
    //Methods that call analogous Entity methods.
    void Update();
    void Render(SDL_Renderer* renderer);
    void HandleInput(SDL_Event &event);
    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);

    //Entity Management and Access.
    Entity& AddEntity(std::string entityName);
    
    bool HasEntities() const { return entities.size() > 0; }
    std::vector<Entity*> GetEntities() const { return entities; }
    unsigned int GetEntityCount() { return entities.size(); }
    Entity* GetEntityByName(std::string entityName);
    void ListAllEntities() const;

    void DestroyInactiveEntities();

private:
    SDL_Renderer* renderer; //A shared pointer.

    std::vector<Entity*> entities;
    
    std::map<const std::string, Entity*> entityNameMap;

    b2World* physWorld;
//    std::shared_ptr<b2World> physWorld;
};
