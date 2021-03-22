 #include "Entity.h"
 
 Entity::Entity(EntityManager& manager) : manager(manager)
 {
     this->isActive = true;
 }

Entity::Entity(EntityManager& manager, std::string name) : manager(manager), name(name)
{
    this->isActive = true;
}

void Entity::Update(b2World* world)
{
    for (auto& component : components)
    {
        component->Update();
    }

    //Check if I HAVE a physics component, but then update pos from it
    xPos = GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().x;
    yPos = GetComponent<PhysicsComponent>()->GetPhysBody()->GetPosition().y;
    std::cout << "XPos: " << xPos << std::endl;
    std::cout << "YPos: " << yPos << std::endl;
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