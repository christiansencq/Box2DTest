#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Box2D/Box2D.h"
#include "SDL2/SDL.h"

#include <bitset>
#include <array>
#include <map>

//Constants

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

constexpr float WINDOW_WIDTH = 1600;
constexpr float WINDOW_HEIGHT = 900;
constexpr float SMALL_SCREEN_W = 400;
constexpr float SMALL_SCREEN_H = 225;

const b2Vec2 puckStart = {SMALL_SCREEN_W/2, SMALL_SCREEN_H/2};


//------ FOR BALL SETUP

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
    {}

    std::array<SDL_Keycode, 3> SwapKeys;
    std::array<SDL_Keycode, 7> ActionKeys;
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

const float TURNSPEED = 0.01;

// Input Related

enum class Actions
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};



// Collision
// COLLISION MASKS  uint16_t  is what is used by the Box2D Filter.
constexpr std::bitset<16> PUCK_BITS = { 1 };
constexpr std::bitset<16> P1GOAL_BITS = { 2 };
constexpr std::bitset<16> P2GOAL_BITS = { 4 };
constexpr std::bitset<16> P1BALL_BITS = { 8 };
constexpr std::bitset<16> P2BALL_BITS = { 16 };
constexpr std::bitset<16> WALL_BITS = { 32 };

enum class ColGroup
{
    PUCK = 1,
    P1GOAL = 2,
    P2GOAL = 4,
    P1BALLS = 8,
    P2BALLS = 16,
    WALLS = 32
};

enum class ColGroups
{
    PUCK = 1 << 0,
    P1_GOAL = 1 << 1
};

#endif
