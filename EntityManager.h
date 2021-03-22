#pragma once

#include <vector>

#include "Entity.h"
    
class EntityManager 
{
public:
 //   EntityManager();

    void ClearData();
    void Update();
    void Render(SDL_Renderer* renderer);

    Entity& AddEntity(std::string entityName);
    
    bool HasEntities() const { return entities.size() > 0; }
    std::vector<Entity*> GetEntities() const { return entities; }
    unsigned int GetEntityCount() { return entities.size(); }
    Entity* GetEntityByName(std::string entityName);
    void ListAllEntities() const;

    void DestroyInactiveEntities();

private:
    std::vector<Entity*> entities;
    SDL_Renderer* renderer;
};
