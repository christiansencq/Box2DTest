#pragma once

#include "Box2D/Box2D.h"
#include <cstdio>
#include <memory>

class DynBody
{
public:
    DynBody(b2World& world);
    ~DynBody();

    void init();
    void update();

    b2Vec2 GetBodyPos() { return mBody->GetPosition(); }

    b2Body* mBody;

private:



    b2World mWorld;

    float xPos;
    float yPos;
    float w;
    float h;
};