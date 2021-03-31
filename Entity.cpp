 #include "Entity.h"
 
 Entity::Entity(EntityManager& manager) : manager(manager)
 {
     this->isActive = true;
 }

Entity::Entity(EntityManager& manager, std::string name) : manager(manager), name(name)
{
    this->isActive = true;
}

void Entity::HandleKeyPress(SDL_Keycode key)
{
    for (auto& component: components)
    {
        component->HandleKeyPress(key);
    }
}

void Entity::HandleKeyRelease(SDL_Keycode key)
{
    for (auto& component: components)
    {
        component->HandleKeyRelease(key);
    }
}


void Entity::HandleEvents(SDL_Event &event)
{
    for (auto& component : components)
    {
        component->HandleEvents(event);
    }
}

void Entity::Update()
{
    for (auto& component : components)
    {
        component->Update();
    }
}

void Entity::Render(SDL_Renderer* renderer)
{
    for (auto& component : components)
    {
        component->Render(renderer);
    }
}

void Entity::Destroy()
{
    this->isActive = false;
}

void Entity::ListAllComponents()
{
    unsigned int i = 0;
    for (auto& component : components)
    {
        component->printType();
        i++;
    }
}