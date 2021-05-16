#include "EntityManager.h"
#include <iostream>
    
void EntityManager::ClearData()
{
    for (auto entity : entities)
    {
        entity->Destroy();
    }
} 

void EntityManager::Update()
{
    for (auto entity : entities)
    {
        entity->Update();
    }

    for (auto p : players)
    {
        p->UpdateSelector();
    }
    //ListAllEntities();entity
    DestroyInactiveEntities();
}

void EntityManager::Render(SDL_Renderer* renderer)
{
    for (auto entity : entities)
    {
        entity->Render(renderer);
    }

    for (auto p : players)
    {
        p->RenderSelector(renderer);
    }
}

void EntityManager::HandleKeyPress(SDL_Keycode key)
{
    for (auto player : players)
    {
        player->HandleKeyPress(key);
    }
}

void EntityManager::HandleKeyRelease(SDL_Keycode key)
{
    for (auto player : players)
    {
        player->HandleKeyRelease(key);
    }
}


Entity* EntityManager::AddEntity()
{
    Entity* entity = new Entity(*this); //Create a new Generic Entity with entityName. Store a pointer to it in entity.
    entities.emplace_back(entity); //Add that pointer to the entities list.
    return entity; //Return the actual object?

    //std::shared_ptr<Entity> entity = std::make_shared<Entity>(*this, entityName);
    //entities.emplace_back(entity);
    //return entity;

}

Entity* EntityManager::AddEntity(b2Vec2 initPixelPos, b2Vec2 initPixelSize)
{
    Entity* entity = new Entity(*this, initPixelPos, initPixelSize); //Create a new Generic Entity with entityName. Store a pointer to it in entity.
    entities.emplace_back(entity); //Add that pointer to the entities list.
    return entity; //Return the actual object?
}

Entity* EntityManager::AddEntity(b2Vec2 initPixelPos, float initPixelRadius)
{
    Entity* entity = new Entity(*this, initPixelPos, initPixelRadius); //Create a new Generic Entity with entityName. Store a pointer to it in entity.
    entities.emplace_back(entity); //Add that pointer to the entities list.
    return entity; //Return the actual object?
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

void EntityManager::AddPlayer(Player* player) 
{
    player->SwapActiveBall(0);
    players.push_back(player);
}