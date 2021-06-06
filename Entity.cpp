#include "Entity.h"

Entity::Entity(EntityManager &manager) : m_Manager(manager) {}

// Rectangle
Entity::Entity(EntityManager &manager, b2Vec2 init_pixel_pos,
               b2Vec2 init_pixel_size)
    : m_Manager(manager), m_PixelPos(init_pixel_pos),
      m_PixelSize(init_pixel_size), isActive(true) {
  SetPixelSize(init_pixel_size);
}

// Circle
Entity::Entity(EntityManager &manager, b2Vec2 init_pixel_pos,
               float init_pixel_rad)
    : m_Manager(manager), m_PixelPos(init_pixel_pos),
      m_PixelRad(init_pixel_rad), isActive(true) {
  SetPixelSize(init_pixel_rad * 2.0f);
}

void Entity::HandleKeyPress(SDL_Keycode key) {
  for (auto &component : m_Components) {
    component->HandleKeyPress(key);
  }
}

void Entity::HandleKeyRelease(SDL_Keycode key) {
  for (auto &component : m_Components) {
    component->HandleKeyRelease(key);
  }
}

// Currently Do I need HandleEvents?  Everything should be covered by
// HandleKeyPress/Release
void Entity::HandleEvents(SDL_Event &event) {
  for (auto &component : m_Components) {
    component->HandleEvents(event);
  }
}

void Entity::Update() {
  // Update my tracking of Position & Angle.
  // TODO : Have each Entity able to have a 'Position' component which is
  // responsible for updating its position (either Physics, static, etc)
  if (HasComponent<PhysicsComponent>()) {
    m_PixelPos.x =
        GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().x * M2P;
    m_PixelPos.y =
        GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().y * M2P;
    m_Angle = GetComponent<PhysicsComponent>()->GetPhysBody()->GetAngle();
  }

  for (auto &component : m_Components) {
    component->Update();
  }
}

void Entity::Render(SDL_Renderer *renderer) {
  for (auto &component : m_Components) {
    component->Render(m_Renderer);
  }
}

void Entity::Destroy() { this->isActive = false; }

void Entity::ListAllComponents() {
  unsigned int i = 0;
  for (auto &component : m_Components) {
    component->printType();
    i++;
  }
}
