#include "TransformComponent.h"

TransformComponent::TransformComponent()
{

}

TransformComponent::TransformComponent(int x, int y, int w, int h)
 : PixelX(x), PixelY(y), Width(w), Height(h)
{
    
}

void TransformComponent::Initialize()
{
    //Set the Variables for Entity?
    //Or should they just remain in Entity...
}

void TransformComponent::Update()
{

}

void TransformComponent::Render(SDL_Renderer* renderer)
{

}