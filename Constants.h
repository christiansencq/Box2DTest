#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Box2D/Box2D.h"
#include "SDL2/SDL.h"
//Constants

//Phys constants - moved to World
// const float timeStep = 1.0f / 60.0f;
// const int velocityIterations = 6;
// const int positionIterations = 2;

constexpr unsigned int SCREEN_WIDTH = 1200;
constexpr unsigned int SCREEN_HEIGHT = 800;
constexpr unsigned int FPS = 60;
constexpr unsigned int FRAME_TARGET_TIME = 1000 / FPS;

constexpr float EPSILON = 0.0001f;

constexpr float M2P = 20;
constexpr float P2M = 1/M2P;

constexpr float TURNSPEED = 0.01;

const b2Vec2 ZEROVEC {0, 0};

const SDL_Color WHITE = {0xFF, 0xFF, 0xFF, 0xFF};
const SDL_Color RED = {0xFF, 0, 0, 0xFF};
const SDL_Color GREEN = {0, 0xFF, 0, 0xFF};
const SDL_Color BLUE = {0, 0, 0xFF, 0xFF};
const SDL_Color PURPLE = {0xDD, 0x11, 0xDD, 0xFF};
const SDL_Color BLACK = {0, 0, 0, 0xFF};

enum class TurnDir
{
    NONE,
    RIGHT,
    LEFT
};

enum class ThrustDir
{
    NONE,
    FORWARD,
    BACKWARD
};

//Not sure if needed
enum class ShapeType
{
    RECT,
    CIRCLE
};

enum class Actions
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

#endif