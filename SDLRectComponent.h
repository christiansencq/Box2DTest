#ifndef SDL_RECT_COMPONENT_H
#define SDL_RECT_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"

#include "Component.h"
#include "Entity.h"

class SDLRectComponent : public Component
{
public:
    SDLRectComponent();
    SDLRectComponent(int x, int y, int w, int h);
    SDLRectComponent(float x, float y, float w, float h);
    ~SDLRectComponent() { delete mRect; }


    void Initialize() {}
    void Update(); //Update will update the coordinates from the owner.
    void Render(SDL_Renderer* renderer);

    SDL_Rect* mRect;
    SDL_Color mColor;
    Entity* owner;

private:


//    Entity* owner;
};

#endif