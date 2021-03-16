#pragma once

#include "Box2D/Box2D.h"

class StatBody
{
public:
    StatBody(b2World& world);
    ~StatBody();

    void init();

private:
    b2Body* mStaticBody;
    b2World mnoptrWorld;

    float xPos;
    float yPos;
    float w;
    float h;
};