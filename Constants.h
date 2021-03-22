#pragma once

//Constants

//Phys constants - moved to World
// const float timeStep = 1.0f / 60.0f;
// const int velocityIterations = 6;
// const int positionIterations = 2;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

//Could just use the b2Vec2D
//These are utility Structures, to make parameters for X,Y & W,H simpler.
struct Coords
{
    float x, y;
};

struct Size2D
{
    float width, height;
};