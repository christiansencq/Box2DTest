//#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <map>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "PhysicsComponent.h"
#include "SDLRectComponent.h"
#include "KeyInputComponent.h"

class EntityManager;

class Entity
{
public:
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name);
    Entity(EntityManager& manager, std::string name, b2Vec2 initPixelPos, b2Vec2 initPixelSize);
    void HandleEvents(SDL_Event &event);
    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);
    void Update();
    void Render(SDL_Renderer* renderer);
    void Destroy();

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args)
    {
        T* newComponent(new T(std::forward<TArgs>(args)...));
        newComponent->owner = this;
        components.emplace_back(newComponent);
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Initialize();
        return *newComponent;
    } 
    
    void ListAllComponents();

    template<typename T>
    T* GetComponent()
    {
        return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }
    
    template <typename T>
    bool HasComponent() const
    {
        //Use by calling like : EntityObj->HasComponent<PhysicsComponent>()
        return componentTypeMap.count(&typeid(T));
    }
    
    bool IsActive() const
    {
        return isActive;//Not sure what purpose this serves.
    }

    std::string GetName() const{ return name; }

    void SetPixelPos(b2Vec2 newScreenPos) { mPixelPos = newScreenPos; }
    void SetPixelSize(b2Vec2 newSize) { mPixelSize = newSize; }

    b2Vec2 GetPhysSize() { return b2Vec2{ mPixelSize.x * P2M, mPixelSize.y * P2M  }; }
    b2Vec2 GetPhysPos() { return b2Vec2{ mPixelPos.x * P2M, mPixelPos.y * P2M }; }
    b2Vec2 GetPixelSize() { return mPixelSize; }
    b2Vec2 GetPixelPos() { return mPixelPos; }

    void ConvertPixelPosToPhysPos();
    void ConvertPixelSizeToPhysSize();

    SDL_Renderer* GetRenderer() {return renderer;}

private:

    EntityManager& manager;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypeMap;
    std::string name;

    b2Vec2 mPixelPos;
    b2Vec2 mPixelSize;
    
    bool isActive;

    //draw from GetComponent<PhysicsComponent>(mPhysBody.position.x, mPhysBody.position.y)
    b2Vec2 mPhysPos;    
    b2Vec2 mPhysSize;

    SDL_Renderer* renderer;
};

#endif