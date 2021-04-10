 #include "Entity.h"
 
 Entity::Entity(EntityManager& manager) 
    : manager(manager), isActive(true)
{

}

Entity::Entity(EntityManager& manager, std::string name)
    : manager(manager), name(name), isActive(true)
{

}

Entity::Entity(EntityManager& manager, std::string name, b2Vec2 initPxPos, b2Vec2 initPxSize)
    : manager(manager), name(name), mPixelPos(initPxPos), mPixelSize(initPxSize),
    isActive(true)
{

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

void Entity::ConvertPixelPosToPhysPos() 
{ 
    //Because the doubles have to be narrowed (which isn't possible in an initializer)

    float newX = mPixelPos.x * 0.1f;
    float newY = mPixelPos.y * 0.1f;
    mPhysPos = {newX, newY};
}

void Entity::ConvertPixelSizeToPhysSize()
{
    float newW = mPixelSize.x * 0.1f;
    float newH = mPixelSize.y * 0.1f;
    mPhysSize = {newW, newH};
}