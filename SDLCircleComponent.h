#ifndef SDL_CIRCLE_COMPONENT_H
#define SDL_CIRCLE_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Entity.h"

class PhysicsComponent;

class SDLCircleComponent : public Component
{
public:
    SDLCircleComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
    ~SDLCircleComponent() { }

    void Initialize();
    void Update(); //Update will update the coordinates from the owner.
    void Render(SDL_Renderer* renderer);

    void DrawCircle();
    void DrawLine(int x0, int y0, int x1, int y1);
    void DisplayAngleIndicator();

    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    float GetPixelX() {return mPixelX; }
    float GetPixelY() {return mPixelY; }

    Entity* GetOwner() { return owner; }
    Entity* owner;


private:
    SDL_Renderer* mnorenderer;
    SDL_Color mColor;

    int mDiameter;
    float mPixelX, mPixelY;
};

#endif