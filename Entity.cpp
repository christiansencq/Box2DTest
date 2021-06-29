#include "Entity.h"

Entity::Entity(EntityManager &manager) : m_Manager(manager) {}

// Rectangle
Entity::Entity(EntityManager &manager, b2Vec2 init_pixel_pos,
               b2Vec2 init_pixel_size)
    : m_Manager(manager), m_PixelPos(init_pixel_pos),
      m_PixelSize(init_pixel_size), isActive(true) 
{
    DetermineAngleFromPosition(m_PixelPos.x);
    m_StartingAngle = m_Angle;
    m_StartingPixelPos = m_PixelPos;

    //Verify that the Vectors have valid Values.
    SetPixelSize(init_pixel_size);
}

// Circle
Entity::Entity(EntityManager &manager, b2Vec2 init_pixel_pos,
               float init_pixel_rad)
    : m_Manager(manager), m_PixelPos(init_pixel_pos),
      m_PixelRad(init_pixel_rad), isActive(true) 
{
    DetermineAngleFromPosition(m_PixelPos.x);
    SetPixelSize(init_pixel_rad * 2.0f);
}

void Entity::DetermineAngleFromPosition(int x_pos)
{
    if (x_pos > SCREEN_WIDTH/2)
    {
        m_Angle = 3.14159;
    }
    else
    {
        m_Angle = 0;
    }

}

void Entity::HandleKeyPress(SDL_Keycode key) 
{
  for (auto &component : m_Components) 
  {
    component->HandleKeyPress(key);
  }
}

void Entity::HandleKeyRelease(SDL_Keycode key) 
{
  for (auto &component : m_Components) 
  {
    component->HandleKeyRelease(key);
  }
}

// Currently Do I need HandleEvents?  Everything should be covered by
// HandleKeyPress/Release
void Entity::HandleEvents(SDL_Event &event) 
{
  for (auto &component : m_Components) 
  {
    component->HandleEvents(event);
  }
}

void Entity::Update() {
  // Update my tracking of Position & Angle.
  // TODO : Have each Entity able to have a 'Position' component which is
  // responsible for updating its position (either Physics, static, etc)
  // TODO: Determine: is this necessary? Just have the PhysicsComponetn call SetPixelPos. Makes much more sense.
  //if (HasComponent<PhysicsComponent>()) 
  //{    m_PixelPos.x =
  //      GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().x * M2P;
  //  m_PixelPos.y =
  //      GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().y * M2P;
  //  m_Angle = GetComponent<PhysicsComponent>()->GetPhysBody()->GetAngle();
  //}

  for (auto &component : m_Components) 
  {
    component->Update();
  }
}

void Entity::Render() {
  for (auto &component : m_Components) 
  {
    component->Render();
  }
}

void Entity::Destroy() 
{ 
    this->isActive = false; 
}

void Entity::ListAllComponents() 
{
  unsigned int i = 0;
  for (auto &component : m_Components) 
  {
    component->printType();
    i++;
  }
}

//void Entity::SetPixelPos(const b2Vec2 newScreenPos)
//{  m_PixelPos = newScreenPos}

void Entity::SetTransform(const b2Vec2 newScreenPos, float angle)
{ 
    m_PixelPos = newScreenPos;

    //Set Body Position
    if (HasComponent<PhysicsComponent>())
    {
        GetComponent<PhysicsComponent>()->SetTransform(b2Vec2 {newScreenPos.x * P2M, newScreenPos.y * P2M}, angle);
    }
    
    //Set Angle.
    m_Angle = angle;
}

void Entity::ResetTransform()
{
    //
    m_Angle = m_StartingAngle;
    m_PixelPos = m_StartingPixelPos;
}
