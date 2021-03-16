#pragma once

#include "Box2D/Box2D.h"
#include "Constants.h"
 
//From:
//https://github.com/borysn/SFML-Box2D-Simple-Level/blob/master/World.h

class World 
{

public:
    World();
    ~World();
    //void setWorld(b2World aWorld);
    b2World* getb2World();
    float getTimeStep() { return timeStep; }
    int getVIterations() { return velocityIterations; }
    int getPIterations() { return positionIterations; }
    
private:

    float timeStep;
    int velocityIterations;
    int positionIterations;

    b2World* world;
    b2Vec2 gravity;
};_w