#ifndef STATE_H
#define STATE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Box2D/Box2D.h"

class State
{
public:
    virtual ~State() {}
    virtual void Init() {}
    virtual void HandleEvents() {}
    virtual void Update() {}
    virtual void Render(SDL_Renderer* renderer) {}

private:

};

#endif
