#pragma once

//CURRENTLY UNUSED

#include <vector>
#include "Box2D/Box2D.h"
#include "SDL2/SDL.h"

#include "Constants.h"
#include "ShapeComponent.h"

class RectShapeComponent : public ShapeComponent
{
public:
    RectShapeComponent();
    RectShapeComponent(const b2Vec2& topLeft, unsigned int width, unsigned int height);
    RectShapeComponent(const b2Vec2& topLeft, const b2Vec2& bottomRight);
    virtual ~RectShapeComponent() {}

    //Component Overrides
    virtual void Initialize() override {}
    virtual void HandleEvents(SDL_Event &event) override {}
    virtual void HandleKeyPress(SDL_Keycode key) override {}
    virtual void Update() override {}
    virtual void Render(SDL_Renderer* renderer) override {}
    virtual void printType() const override {}

    //Getters
    b2Vec2 GetTopLeftPoint() const { return mPoints[0]; }
    b2Vec2 GetBottomRightPoint() const { return mPoints[1]; }
    int GetWidth() const { return mPoints[1].x - mPoints[0].x; }
    int GetHeight() const { return mPoints[1].y - mPoints[0].y; }
    virtual b2Vec2 GetCenterPoint() const override;
    virtual std::vector<b2Vec2> GetPoints() const override;

    //Setters
    inline void SetTopLeftPoint(const b2Vec2& topLeft) {mPoints[0] = topLeft;}
    inline void SetBottomRightPoint(const b2Vec2& bottomRight) {mPoints[1] = bottomRight;}
    void MoveTo(const b2Vec2& position);

    //For drawing, would for now be easiest to just create an SDL_Rect and use SDL_Rect_Fill.   
    //SDL_Rect* UpdateSDLRect();

    Entity* owner;

private:
    SDL_Rect mRect;
};