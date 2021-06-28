#ifndef SDL_CIRCLE_COMPONENT_H
#define SDL_CIRCLE_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Box2D/Box2D.h"

//#include "../Entity.h"
#include "../Constants.h"
#include "Component.h"

//class PhysicsComponent;
class Entity;

class SDLCircleComponent : public Component
{
public:
    explicit SDLCircleComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
    ~SDLCircleComponent() { }

    virtual void Initialize() override;
    virtual void Update() override; 
    virtual void Render() override;

    void DrawCircle();
    void DrawLine(int x0, int y0, int x1, int y1);
    void DisplayAngleIndicator();

    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    float GetPixelX() {return m_PixelX; }
    float GetPixelY() {return m_PixelY; }

    Entity* GetOwner() { return owner; }
    Entity* owner;


private:
    SDL_Renderer* m_Renderer;
    SDL_Color m_Color;

    int m_Diameter;
    float m_PixelX, m_PixelY;
};

#endif
