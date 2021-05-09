#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"

class TransformComponent : public Component
{
public:
    TransformComponent();
    TransformComponent(int x, int y, int w, int h);

    void Initialize();
    void Update(); //Update will update the coordinates from the owner.
    void Render(SDL_Renderer* renderer);

    int PixelX, PixelY;
    int Width, Height;
    


private:


};




#endif
