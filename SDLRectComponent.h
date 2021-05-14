#ifndef SDL_RECT_COMPONENT_H
#define SDL_RECT_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Constants.h"
#include "Entity.h"

class PhysicsComponent;

class SDLRectComponent : public Component
{
public:
    //SDLRectComponent(SDL_Renderer* renderer, int PixelW, int PixelH, SDL_Color color = BLACK);
    SDLRectComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
    ~SDLRectComponent() { }

    void Initialize();
    void Update(); //Update will update the coordinates from the owner.
    void Render(SDL_Renderer* renderer);

    void DrawLine(int x0, int y0, int x1, int y1);
    void DrawShape(b2Vec2* points, int numSegments); 
    
    void DisplayRect();
    
    void DisplayAngleIndicator();
    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    Entity* GetOwner() { return owner; }
    Entity* owner;
    b2Body* mPhysBody;


private:
    SDL_Renderer* mnorenderer;
//void DrawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1);
    bool IsDynamic;

    int mWidth, mHeight;
    int mPixelX, mPixelY;
    SDL_Color mColor;
};

#endif