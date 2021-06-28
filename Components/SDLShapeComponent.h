#ifndef SDL_SHAPE_COMPONENT_H
#define SDL_SHAPE_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

//#include "Const/Constants.h"
//#include "Entity.h"

//class PhysicsComponent;

// class ShapeComponent : public Component
// {
// public:
//     //SDLRectComponent(SDL_Renderer* renderer, int PixelW, int PixelH, SDL_Color color = BLACK);
//     //SDLRectComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
//     virtual ~ShapeComponent() { }

//     virtual void Initialize();
//     virtual void Update(); //Update will update the coordinates from the owner.
//     virtual void Render();

//     virtual void DrawLine(int x0, int y0, int x1, int y1);
//     virtual void DrawShape(b2Vec2* points, int numSegments); 
    
//     void DisplayRect();
    
//     virtual void DisplayAngleIndicator();
//     virtual void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

//     std::shared_ptr<Entity> owner;
//     b2Body* mPhysBody;


// private:
//     SDL_Renderer* mnorenderer;
// //void DrawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1);
//     bool IsDynamic;

//     int mWidth, mHeight;
//     int mPixelX, mPixelY;
//     SDL_Color mColor;
// };

#endif