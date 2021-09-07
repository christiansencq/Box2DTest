#include "SDLCircleComponent.h"
#include "../Entity.h"

SDLCircleComponent::SDLCircleComponent(SDL_Renderer* renderer, SDL_Color color)
    : m_Renderer(renderer), m_Color(color)
{ }

void SDLCircleComponent::Initialize() 
{
    m_Diameter = owner->GetPixelSize().x;
    Update();
}

void SDLCircleComponent::Update()
{
    m_PixelX = owner->GetPixelPos().x;
    m_PixelY = owner->GetPixelPos().y;
}

void SDLCircleComponent::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
    DrawShape();
}

void SDLCircleComponent::DrawShape()
{
    
    int32_t x = (m_Diameter/2 - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - m_Diameter);

    while (x >= y)
    {
    //  Each of the following renders an octant of the circle
    //Uses midpoint algorithm to draw
        SDL_RenderDrawPoint(m_Renderer, m_PixelX + x, m_PixelY - y);
        SDL_RenderDrawPoint(m_Renderer, m_PixelX + x, m_PixelY + y);
        SDL_RenderDrawPoint(m_Renderer, m_PixelX - x, m_PixelY - y);
        SDL_RenderDrawPoint(m_Renderer, m_PixelX - x, m_PixelY + y);
        SDL_RenderDrawPoint(m_Renderer, m_PixelX + y, m_PixelY - x);
        SDL_RenderDrawPoint(m_Renderer, m_PixelX + y, m_PixelY + x);
        SDL_RenderDrawPoint(m_Renderer, m_PixelX - y, m_PixelY - x);
        SDL_RenderDrawPoint(m_Renderer, m_PixelX - y, m_PixelY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0)
        {
            --x;
            tx += 2;
        error += (tx - m_Diameter);
        }
    }
    DisplayAngleIndicator();
}


void SDLCircleComponent::DisplayAngleIndicator()
{ 
  SDL_SetRenderDrawColor(m_Renderer, 200, 50, 50, 255);

  b2Vec2 center {m_PixelX, m_PixelY};

  b2Vec2 endpoint {center.x + m_Diameter/2 * cos(owner->GetAngle()), 
                   center.y + m_Diameter/2 * sin(owner->GetAngle())};
  // SDL_RenderDrawPoints(m_Renderer
  DrawLine(center.x, center.y, endpoint.x, endpoint.y);
}

void SDLCircleComponent::DrawLine(int x0, int y0, int x1, int y1)
{
    //May need to convert to a line drawn by pixels.
    //Calculate the points from the center to the edge
    

    SDL_RenderDrawLine(m_Renderer, x0, y0, x1, y1);
}

void SDLCircleComponent::RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle)
{
    //Rotate the points around the 'center'
    b2Vec2 tmp;
    tmp.x = vector.x * cos(angle) - vector.y * sin(angle);
    tmp.y = vector.x * sin(angle) + vector.y * cos(angle);
    vector = tmp + center;
}
