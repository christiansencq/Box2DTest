#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <memory>
#include <vector>

#include "Entity.h"

#include "Player.h"

class EntityManager {
public:
  void ClearData();

  // Methods that call analogous Entity methods; Game loop Methods.
  void Update();
  void Render(SDL_Renderer *renderer);
  void HandleInput(SDL_Event &event) {}
  void HandleKeyPress(SDL_Keycode key);
  void HandleKeyRelease(SDL_Keycode key);

  // Entity Management and Access.
  Entity *AddEntity();
  Entity *AddEntity(b2Vec2 initPixelPos, b2Vec2 initPixelSize);
  Entity *AddEntity(b2Vec2 initPixelPos, float initPixelRadius);

  bool HasEntities() const { return m_Entities.size() > 0; }
  std::vector<Entity *> GetEntities() const { return m_Entities; }
  unsigned int GetEntityCount() const { return m_Entities.size(); }

  void DestroyInactiveEntities();
  void AddPlayer(Player *player);

private:
  SDL_Renderer *m_Renderer; // A shared pointer.
  // std::vector<std::shared_ptr<Entity>> entities;
  std::vector<Entity *> m_Entities;
  std::vector<Player *> m_Players;
  // std::map<const std::string, Entity*> entityNameMap;
  b2World *m_PhysWorld;
};
#endif
