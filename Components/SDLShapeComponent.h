#ifndef SDL_SHAPE_COMPONENT_H
#define SDL_SHAPE_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../Constants.h"
#include "Component.h"

class Entity;
class PhysicsComponent;

class ShapeComponent : public Component
{
public:
    virtual ~ShapeComponent() { }

    virtual void Initialize() override {}
    virtual void Update() override {}

    virtual void DisplayAngleIndicator() {}
    virtual void DrawShape() {}

    virtual float GetPixelX() { return m_PixelX; }
    virtual float GetPixelY() { return m_PixelY; }

    virtual void Render() override 
    { 
        SDL_SetRenderDrawColor(m_Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
        DrawShape(); 
    }


    void DrawLine(int x0, int y0, int x1, int y1) 
    {
        SDL_RenderDrawLine(m_Renderer, x0, y0, x1, y1);
    }
    //
    // void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle) 
    // {
    //     b2Vec2 tmp;
    //     tmp.x = vector.x * cos(angle) - vector.y * sin(angle);
    //     tmp.y = vector.x * sin(angle) + vector.y * cos(angle);
    //     vector = tmp + center;
    // }

private:
    SDL_Renderer* m_Renderer;
    SDL_Color m_Color;
    float m_PixelX, m_PixelY;
};

#endif
