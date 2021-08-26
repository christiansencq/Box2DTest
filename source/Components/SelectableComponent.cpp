#include "SelectableComponent.h"
#include "../Entity.h"

SelectableComponent::SelectableComponent(SDL_Renderer* renderer, std::vector<int> color)
 : m_Renderer(renderer), isSelected(false), m_Color(RED), m_PixelX(0), m_PixelY(0)
{
    m_Color.r = color[0];
    m_Color.g = color[1];
    m_Color.b = color[2];
    m_Color.a = color[3];
}

SelectableComponent::SelectableComponent(SDL_Renderer* renderer, SDL_Color color)
 : m_Renderer(renderer), isSelected(false), m_Color(RED), m_PixelX(0), m_PixelY(0)
{
    m_Color = color;
}

SelectableComponent::SelectableComponent(SDL_Renderer* renderer )
 : m_Renderer(renderer), isSelected(false), m_Color(RED), m_PixelX(0), m_PixelY(0)
{

}

SelectableComponent::~SelectableComponent()
{

}


void SelectableComponent::Initialize()
{
    m_PixelX = owner->GetPixelPos().x;
    m_PixelY = owner->GetPixelPos().y;
}

void SelectableComponent::Render()
{
    if (isSelected)
    {
        // SDL_SetRenderDrawColor(m_Renderer, player->, m_Color.g, m_Color.b, m_Color.a);
        SDL_SetRenderDrawColor(m_Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
        DrawCircle();      
    }
}

// void SelectableComponent::SetColor(std::vector<int> color)
// {
//     m_Color.r = color[0];
//     m_Color.g = color[1];
//     m_Color.b = color[2];
//     m_Color.a = color[3];
// }
//
void SelectableComponent::DrawCircle()
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
}

void SelectableComponent::Update()
{
    if (isSelected)
    {
        m_Diameter = owner->GetRadius() + addRad;
        m_PixelX = owner->GetPixelPos().x;
        m_PixelY = owner->GetPixelPos().y;
    }
}
