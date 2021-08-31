#ifndef SDL_CIRCLE_COMPONENT_H
#define SDL_CIRCLE_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Box2D/Box2D.h"

#include "Constants.h"
#include "Component.h"
//#include "SDLShapeComponent.h"

class Entity;

class SDLCircleComponent : public Component
{
public:
    SDLCircleComponent(SDL_Renderer* renderer, SDL_Color color = RED);
    virtual ~SDLCircleComponent() { }

    virtual void Initialize() override;
    virtual void Update() override; 
    virtual void Render() override;

    void DrawLine(int x0, int y0, int x1, int y1);
    void DrawShape();

    void DisplayAngleIndicator();
    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    float GetX() { return m_PixelX; }
    float GetY() { return m_PixelY; }
    Entity* GetOwner() { return owner; }
    Entity* owner;

private:
    SDL_Renderer* m_Renderer;
    SDL_Color m_Color;

    float m_Diameter;
    float m_PixelX, m_PixelY;
};

#endif
