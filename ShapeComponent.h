#pragma once

#include "Box2D/Box2D.h"
#include <vector>

#include "Component.h"

class ShapeComponent : public Component
{
public:
    virtual ~ShapeComponent() {}

    //Component Overrides.
    virtual void Initialize() override {}
    virtual void HandleEvents(SDL_Event &event) override{}
    virtual void HandleKeyPress(SDL_Keycode key) override {}
    virtual void Update() override {}
    virtual void Render(SDL_Renderer* renderer) override {}
    virtual void printType() const override {}

    //Getters
    virtual b2Vec2 GetCenterPoint() const { return b2Vec2{ mPoints[1].x-mPoints[0].x, mPoints[1].y - mPoints[0].y} ;}
    virtual std::vector<b2Vec2> GetPoints() const { return mPoints; }

    //Setters
    void MoveBy(const b2Vec2& deltaOffset);

    Entity* owner;

protected:
    std::vector<b2Vec2> mPoints;
};