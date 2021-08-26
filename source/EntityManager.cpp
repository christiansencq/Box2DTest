#include "EntityManager.h"
#include <iostream>
    
void EntityManager::ClearData()
{
    for (auto& entity : m_Entities)
    {
        entity->Destroy();
    }
} 

void EntityManager::Update()
{
    for (auto& entity : m_Entities)
    {
        entity->Update();
    }

    for (auto& p : m_Players)
    {
        p->UpdateSelector();
    }

    DestroyInactiveEntities();
}

void EntityManager::Render(SDL_Renderer* renderer)
{
    for (auto& entity : m_Entities)
    {
        entity->Render();
    }

    for (auto& p : m_Players)
    {
        p->RenderSelector(renderer);
    }
}

Entity* EntityManager::AddEntity()
{
    Entity* entity = new Entity(*this); 
    m_Entities.emplace_back(entity); 
    return entity; 
}

Entity* EntityManager::AddEntity(b2Vec2 initPixelPos, b2Vec2 initPixelSize)
{
    Entity* entity = new Entity(*this, initPixelPos, initPixelSize); 
    m_Entities.emplace_back(entity); 
    return entity; 
}

Entity* EntityManager::AddEntity(b2Vec2 initPixelPos, float initPixelRadius)
{
    Entity* entity = new Entity(*this, initPixelPos, initPixelRadius);
    m_Entities.emplace_back(entity);
    return entity;
}

void EntityManager::DestroyInactiveEntities()
{
    for (size_t i = 0; i < m_Entities.size(); i++) 
    {
        if (!m_Entities[i]->IsActive())
        {
            m_Entities.erase(m_Entities.begin() + i);
        }
    }
}

void EntityManager::AddPlayer(std::shared_ptr<Player> player) 
{
    // player->SwapActiveBall(0);
    m_Players.push_back(player);
}

void EntityManager::ResetStage()
{
    for (Entity* ent : m_Entities)
    {
        ent->ResetTransform();
    }
}

