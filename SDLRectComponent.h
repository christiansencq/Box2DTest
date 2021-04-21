#ifndef SDL_RECT_COMPONENT_H
#define SDL_RECT_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Constants.h"
//#include "Component.h"
#include "Entity.h"
//#include "PhysicsComponent.h"

//#include "Utilities/Coords2D.h"

class PhysicsComponent;

class SDLRectComponent : public Component
{
public:
    // SDLRectComponent();
    // SDLRectComponent(SDL_Renderer* renderer, int PixelW, int PixelH);
    SDLRectComponent(SDL_Renderer* renderer, int PixelW, int PixelH, SDL_Color color = BLACK);
    ~SDLRectComponent() { }

    void Initialize();
    void Update(); //Update will update the coordinates from the owner.
    void Render(SDL_Renderer* renderer);

    //void DrawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1);
    void DrawLine(int x0, int y0, int x1, int y1);

    void DrawRect(b2Vec2* points, b2Vec2 center, float angle);
    void DisplayRect(b2World* world);
    void DisplayAngleIndicator(b2World* world, b2Body* tmpbody);
    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    Entity* owner;
    PhysicsComponent* physicsComp; //NOT owned Component, just a Pointer to the Component of the shared Entity.

private:

    SDL_Renderer* mnorenderer;

    int mWidth, mHeight;

    SDL_Color mColor;
};

#endif