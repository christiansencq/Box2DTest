#include "BoxWorld.h"

World::World() 
{
    gravity = b2Vec2(0.0f, -10.0f);
    world = new b2World(gravity);
    
}

b2World* World::getb2World()
{
    return world;
}

float World::getTimeStep()
{
    return timeStep;
}

int World::getVIterations()
{
    return velocityIterations;
}

int World::getPIterations()
{
    return positionIterations;
}

World::~World()
{
    delete world;
    world = NULL;
}