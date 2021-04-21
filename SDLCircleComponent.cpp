#include "SDLCircleComponent.h"

SDLCircleComponent::SDLCircleComponent() : SDLCircleComponent(0, 0, 1) { }

SDLCircleComponent::SDLCircleComponent(int PixelX, int PixelY, int PixelR)
    : mColor(BLUE)
{

}

void SDLCircleComponent::Initialize() 
{
  physics = owner->GetComponent<PhysicsComponent>();
}

void SDLCircleComponent::Update()
{

}

void SDLCircleComponent::Render(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
  DisplayCirc(renderer, physics->GetPhysBody()->GetWorld());
}

void SDLCircleComponent::DisplayCirc(SDL_Renderer* renderer, b2World* world)
{
 b2Body* tmpbody = physics->GetPhysBody();
 


}

void SDLCircleComponent::DrawLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1)
{

}

void SDLCircleComponent::DrawCirc(SDL_Renderer* renderer, b2Vec2* points, b2Vec2 center, float angle, int radius)
{
    const int diameter = (radius * 2);
    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, center.x + x, center.y - y);
        SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
        SDL_RenderDrawPoint(renderer, center.x - x, center.y - y);
        SDL_RenderDrawPoint(renderer, center.x - x, center.y + y);
        SDL_RenderDrawPoint(renderer, center.x + y, center.y - x);
        SDL_RenderDrawPoint(renderer, center.x + y, center.y + x);
        SDL_RenderDrawPoint(renderer, center.x - y, center.y - x);
        SDL_RenderDrawPoint(renderer, center.x - y, center.y + x);        
    
        if (error <= 0)
        {
            ++y;
            error += ty;
            ty +=2;
        }

        if (error > 0)
        {
            --x;
            tx +=2;
            error += (tx - diameter);
        }
    }
}

void SDLCircleComponent::RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle)
{

}