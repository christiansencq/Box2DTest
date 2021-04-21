#ifndef SDL_CIRCLE_COMPONENT_H
#define SDL_CIRCLE_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Constants.h"
#include "Entity.h"

class PhysicsComponent;

class SDLCircleComponent : public Component
{
public:
    SDLCircleComponent();
    SDLCircleComponent(int PixelX, int PixelY, int PixelR);
    ~SDLCircleComponent() { }

    void Initialize();
    void Update(); //Update will update the coordinates from the owner.
    void Render(SDL_Renderer* renderer);

    void DrawLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);

    void DrawCirc(SDL_Renderer* renderer, b2Vec2* points, b2Vec2 center, float angle, int radius);
    void DisplayCirc(SDL_Renderer* renderer, b2World* world);

    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    Entity* owner;
    PhysicsComponent* physics; 

private:
    SDL_Color mColor;
};


#endif