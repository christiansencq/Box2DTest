#ifndef SDL_RECT_COMPONENT_H
#define SDL_RECT_COMPONENT_H

#include <array>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../Constants.h"
#include "Component.h"

//Problematic coupling here: 
//#include "PhysicsComponent.h"

class Entity;

class SDLRectComponent : public Component
{
public:
    //SDLRectComponent(SDL_Renderer* renderer, int PixelW, int PixelH, SDL_Color color = BLACK);
    SDLRectComponent(SDL_Renderer* renderer, SDL_Color color = BLACK);
    ~SDLRectComponent() { }

    void Initialize() override;
    void Update() override; //Update will update the coordinates from the owner.
    void Render() override;

    void DrawLine(int x0, int y0, int x1, int y1);
    void DrawShape(b2Vec2* points, int numSegments); 
    
    void DisplayRect();
    
    void DisplayAngleIndicator();
    void RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle);

    Entity* GetOwner() { return owner; }
    Entity* owner;
    b2Body* m_PhysBody;


private:
    SDL_Renderer* m_Renderer;
    bool IsDynamic;
    int m_Width, m_Height;
    int m_PixelX, m_PixelY;
    SDL_Color m_Color;
};

#endif
