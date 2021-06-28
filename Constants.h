#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Box2D/Box2D.h"
#include "SDL2/SDL.h"

#include <array>
#include <map>
//Constants

//Phys constants - moved to World
// const float timeStep = 1.0f / 60.0f;
// const int velocityIterations = 6;
// const int positionIterations = 2;


constexpr unsigned int FPS = 60;

constexpr unsigned int FRAME_TARGET_TIME = 1000 / FPS;//Convert FPS to milliseconds per frame?

constexpr float EPSILON = 0.0001f;

constexpr float M2P = 20;
constexpr float P2M = 1/M2P;

const b2Vec2 ZEROVEC {0, 0};

const SDL_Color WHITE = {0xFF, 0xFF, 0xFF, 0xFF};
const SDL_Color RED = {0xFF, 0, 0, 0xFF};
const SDL_Color GREEN = {0, 0xFF, 0, 0xFF};
const SDL_Color BLUE = {0, 0, 0xFF, 0xFF};
const SDL_Color PURPLE = {0xDD, 0x11, 0xDD, 0xFF};
const SDL_Color BLACK = {0, 0, 0, 0xFF};
const SDL_Color YELLOW = {0xFF, 0xFF, 0, 0xFF};
const SDL_Color CYAN = {0, 0xFF, 0xFF, 0xFF};


//-----FOR ARENA SETUP -------------- 

constexpr float SCREEN_WIDTH = 1600;
constexpr float SCREEN_HEIGHT = 900;

//Wall Thickness
constexpr float WALL_THICKNESS = 10.f;
//WallBuffer
constexpr float WALL_BUFFER = 50.f;

//Spawn locations
// b2Vec2 p1startPos1 = {350, 640};
// b2Vec2 p1startPos2 = {350, 480};
// b2Vec2 p1startPos3 = {350, 320};

const b2Vec2 puckStart = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

// std::array<b2Vec2, 3> P1StartingPos = {p1startPos1, p1startPos2, p1startPos3};





//------ FOR BALL SETUP



//Rename to EntityShape
enum class ShapeType
{
    RECT,
    CIRCLE
};

enum class PhysBodyType
{
    DYNAMIC,
    KINEMATIC,
    STATIC
};

enum class isSensor
{
    False,
    True
};






struct KeyBinding
{
    KeyBinding(std::array<SDL_Keycode,3> swap_keys, std::array<SDL_Keycode, 7> action_keys)
    : SwapKeys(swap_keys), ActionKeys(action_keys)
    {

    }

    std::array<SDL_Keycode, 3> SwapKeys;
    std::array<SDL_Keycode, 7> ActionKeys;

};

// std::array<SDL_Keycode, 3> P1SwapKeyBinds = { SDLK_i, SDLK_o, SDLK_p };
// std::array<SDL_Keycode, 7> P1ActionKeyBinds = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_j, SDLK_k, SDLK_l };

enum class ColGroups
{
    PUCK = 1 << 0,
    P1_GOAL = 1 << 1
//    P2_GOAL = 1 << 2,

};


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

enum class Actions
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

constexpr float TURNSPEED = 0.01;
// COLLISION MASKS
constexpr int mask0{ 0b0000'0001 }; //Puck
constexpr int mask1{ 0b0000'0010 }; //P1Goal
constexpr int mask2{ 0b0000'0100 }; //P2Goal
constexpr int mask3{ 0b0000'1000 }; //P1Balls
constexpr int mask4{ 0b0001'0000 }; //P2Balls
constexpr int mask5{ 0b0010'0000 }; //Walls
constexpr int mask6{ 0b0100'0000 };
constexpr int mask7{ 0b1000'0000 };

#endif
