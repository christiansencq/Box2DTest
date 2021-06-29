#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <vector>

#include "Box2D/Box2D.h"
#include "SDL2/SDL.h"

#include "Constants.h"
#include "Components/Component.h"

#include "Components/PhysicsComponent.h"
#include "Components/GoalZoneComponent.h"
#include "Components/TextComponent.h"
#include "Components/KeyInputComponent.h"
#include "Components/SDLCircleComponent.h"
#include "Components/SDLRectComponent.h"
#include "Components/SelectableComponent.h"

class EntityManager;

class Entity {
public:
    explicit Entity(EntityManager &manager);
    Entity(EntityManager &manager, b2Vec2 init_pixel_pos, b2Vec2 init_pixel_size);
    Entity(EntityManager &manager, b2Vec2 init_pixel_pos, float init_pixel_rad);

    void HandleEvents(SDL_Event &event);
    void HandleKeyPress(SDL_Keycode key);
    void HandleKeyRelease(SDL_Keycode key);
    void Update();
    void Render();
    void Destroy();

  //Component Management.
    void ListAllComponents();

  template <typename T, typename... TArgs> T &AddComponent(TArgs &&...args) {
    // Call would look like : EntityName->AddComponent<ComponentType>(Arguments)
    T *newComponent(new T(std::forward<TArgs>(args)...));
    newComponent->owner = this;
    m_Components.emplace_back(newComponent);
    m_ComponentTypeMap[&typeid(*newComponent)] = newComponent;
    newComponent->Initialize();
    return *newComponent;
  }

  template <typename T> T *GetComponent() {
    return static_cast<T *>(m_ComponentTypeMap[&typeid(T)]);
  }

  template <typename T> bool HasComponent() const {
    return m_ComponentTypeMap.count(&typeid(T));
  }

  bool IsActive() const {
    return isActive; // Not sure what purpose this serves.
  }

  //Accessors
  void SetPixelSize(const b2Vec2 newSize) { m_PixelSize = newSize; }
  void SetPixelSize(const float newRadius) {
    m_PixelRad = newRadius;
    m_PixelSize = b2Vec2{m_PixelRad, m_PixelRad};
  }

  void SetPixelPos(const b2Vec2 newScreenPos) { m_PixelPos = newScreenPos;}   
  void SetAngle(float new_angle) { m_Angle = new_angle; }
  void SetTransform(const b2Vec2 newScreenPos, float angle);
  //void DetermineAngleFromPosition(int x_pos);//Later change this to the pos vector, so we can rotate toward?
  void SignalManagerToReset(); 
  void ResetTransform();

  b2Vec2 GetPhysSize() { return b2Vec2{ m_PixelSize.x * P2M, m_PixelSize.y * P2M }; }
  b2Vec2 GetPhysPos() { return b2Vec2{ m_PixelPos.x * P2M, m_PixelPos.y * P2M }; }

  b2Vec2 GetPixelSize() { return m_PixelSize; }
  b2Vec2 GetPixelPos() { return m_PixelPos; }

  int GetRadius() { return m_PixelRad; }
  float GetAngle() { return m_Angle; }



// SDL_Renderer *GetRenderer() { return m_Renderer; }

private:
  EntityManager& m_Manager;

  std::vector<Component*> m_Components;
  //    std::vector<std::unique_ptr<Component>> components;
  std::map<const std::type_info*, Component*> m_ComponentTypeMap;

  b2Vec2 m_PixelPos;
  b2Vec2 m_PixelSize;
  float m_PixelRad;
  float m_Angle;

  bool isActive;

  b2Vec2 m_StartingPixelPos;
  float m_StartingAngle;

};

#endif
