//#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <map>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "Constants.h"

#include "PhysicsComponent.h"
#include "SDLRectComponent.h"
#include "SDLCircleComponent.h"
#include "KeyInputComponent.h"
#include "SelectableComponent.h"
#include "TextComponent.h"

class EntityManager;

class Entity
{
public:
    // Entity(EntityManager& manager);//Because these are references, they MUST be initialized.
    // Entity(EntityManager& manager, b2Vec2 init_pixel_pos, b2Vec2 init_pixel_size);
    // Entity(EntityManager& manager, b2Vec2 init_pixel_pos, float init_pixel_size);

    Entity(EntityManager& manager);
    Entity(EntityManager& manager, b2Vec2 init_pixel_pos, b2Vec2 init_pixel_size);
    Entity(EntityManager& manager, b2Vec2 init_pixel_pos, float init_pixel_size);

    void HandleEvents(SDL_Event &event);
    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);
    void Update();
    void Render(SDL_Renderer* renderer);
    void Destroy();

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args)
    {
        //Call would look like : EntityName->AddComponent<ComponentType>(Arguments)
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

    void SetPixelPos(const b2Vec2 newScreenPos) { mPixelPos = newScreenPos; }
    void SetPixelSize(const b2Vec2 newSize) { mPixelSize = newSize; }
    void SetPixelSize(const float newRadius) { mPixelRad = newRadius;
                                         mPixelSize = b2Vec2 {mPixelRad, mPixelRad}; }

    b2Vec2 GetPhysSize() { return b2Vec2{ mPixelSize.x * P2M, mPixelSize.y * P2M  }; }
    b2Vec2 GetPhysPos() { return b2Vec2{ mPixelPos.x * P2M, mPixelPos.y * P2M }; }
    b2Vec2 GetPixelSize() { return mPixelSize; }
    b2Vec2 GetPixelPos() { return mPixelPos; }
    int GetRadius() {return mPixelRad; }
    float GetAngle() { return mAngle; }
    

    // void ConvertPixelPosToPhysPos();
    // void ConvertPixelSizeToPhysSize();

    SDL_Renderer* GetRenderer() {return renderer;}

private:

    EntityManager& manager;

    std::vector<Component*> components;
//    std::vector<std::unique_ptr<Component>> components;
    std::map<const std::type_info*, Component*> componentTypeMap;


    b2Vec2 mPixelPos;
    b2Vec2 mPixelSize;
    float mPixelRad;
    float mAngle;

    bool isActive;

    SDL_Renderer* renderer;
};

#endif