#include "EntityManager.h"
#include <iostream>
    
void EntityManager::ClearData()
{
    for (auto& entity : entities)
    {
        entity->Destroy();
    }
} 

void EntityManager::Update()
{
    for (auto& entity : entities)
    {
        entity->Update();
    }
    ListAllEntities();
    DestroyInactiveEntities();
}

void EntityManager::Render(SDL_Renderer* renderer)
{
    for (auto& entity : entities)
    {
        entity->Render(renderer);
    }
}

Entity& EntityManager::AddEntity(std::string entityName)
{
    Entity* entity = new Entity(*this, entityName); //Create a new Generic Entity with entityName. Store a pointer to it in entity.
    entities.emplace_back(entity); //Add that pointer to the entities list.
    return *entity; //Return the actual object?
}

void EntityManager::DestroyInactiveEntities()
{
    for (size_t i = 0; i < entities.size(); i++) 
    {
        if (!entities[i]->IsActive())
        {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::ListAllEntities() const
{
    for (auto& entity : entities)
    {
        std::cout << entity->GetName() << std::endl;
    }
}
