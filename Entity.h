#pragma once

#include <string>
#include <vector>
#include <map>

#include "PhysicsComponent.h"
//#include "EntityManager.h"

class EntityManager;

class Entity
{
public:
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name);
    
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
        return componentTypeMap.count(&typeid(T));
    }
    
    bool IsActive() const
    {
        return isActive;
    }

    std::string GetName() const{ return name; }
    float xPos, yPos;

private:

    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypeMap;
    std::string name;

    //b2World* physWorld;
    SDL_Renderer* renderer;
};