#ifndef SDL_RECT_COMPONENT_H
#define SDL_RECT_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../Constants.h"
#include "SDLShapeComponent.h"
//Problematic coupling here: 
//#include "PhysicsComponent.h"

class Entity;
class SDLRectComponent : public ShapeComponent
{
public:
    explicit SDLRectComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
    virtual ~SDLRectComponent() { }

    virtual void Initialize() override;
    virtual void Update() override;
//    virtual void Render() override;

    virtual void DrawLine(int x0, int y0, int x1, int y1) override;
    virtual void DrawShape() override; 
    
    virtual void DisplayAngleIndicator() override;
    virtual void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle) override;

    Entity* owner;

private:
    SDL_Renderer* m_Renderer;
    b2Body* m_PhysBody;
    bool IsDynamic;
    int m_Width, m_Height;
    int m_PixelX, m_PixelY;
    SDL_Color m_Color;
};

#endif
