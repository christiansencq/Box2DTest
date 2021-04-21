 #include "Entity.h"
 
 Entity::Entity(EntityManager& manager) 
    : Entity(manager, std::string("NoName"))
{

}

Entity::Entity(EntityManager& manager, std::string name)
    : Entity(manager, name, b2Vec2{0, 0}, b2Vec2{0, 0})
{

}

Entity::Entity(EntityManager& manager, std::string name, b2Vec2 initPxPos, b2Vec2 initPxSize)
    : manager(manager), name(name), mPixelPos(initPxPos), mPixelSize(initPxSize), isActive(true)
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

    float newX = mPixelPos.x * P2M;
    float newY = mPixelPos.y * P2M;
    mPhysPos = {newX, newY};
}

void Entity::ConvertPixelSizeToPhysSize()
{
    float newW = mPixelSize.x * P2M;
    float newH = mPixelSize.y * P2M;
    mPhysSize = {newW, newH};
}