#ifndef SDL_RECT_COMPONENT_H
#define SDL_RECT_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../Constants.h"
#include "Component.h"
//#include "SDLShapeComponent.h"

class Entity;
class SDLRectComponent : public Component
{
public:
    explicit SDLRectComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
    virtual ~SDLRectComponent() { }

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override
    {
        SDL_SetRenderDrawColor(m_Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
        DrawShape(); 
    }

    Entity* owner;

private:
    void DisplayAngleIndicator();
    void DrawShape(); 
    void DrawLine(int x0, int y0, int x1, int y1);
    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    SDL_Renderer* m_Renderer;
    b2Body* m_PhysBody;
    bool IsDynamic;
    int m_Width, m_Height;
    int m_PixelX, m_PixelY;
    SDL_Color m_Color;
};

#endif
