#ifndef SDL_CIRCLE_COMPONENT_H
#define SDL_CIRCLE_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Box2D/Box2D.h"

#include "../Constants.h"
#include "SDLShapeComponent.h"

class Entity;

class SDLCircleComponent : public ShapeComponent
{
public:
    explicit SDLCircleComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
    virtual ~SDLCircleComponent() { }

    virtual void Initialize() override;
    virtual void Update() override; 

//    virtual void DrawLine(int x0, int y0, int x1, int y1) override;
    virtual void DrawShape() override;

    virtual void DisplayAngleIndicator() override;
    virtual void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle) override;

    Entity* GetOwner() { return owner; }
    Entity* owner;

private:
    SDL_Renderer* m_Renderer;
    SDL_Color m_Color;

    float m_Diameter;
    float m_PixelX, m_PixelY;
};

#endif
