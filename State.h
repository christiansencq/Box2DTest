#ifndef STATE_H
#define STATE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Box2D/Box2D.h"

class State
{
public:
    virtual ~State() {}
    virtual void init() = 0;
    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;

private:

};

#endif