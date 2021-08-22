#ifndef ARENA_LAYOUT_H
#define ARENA_LAYOUT_H

#include <vector>

#include "Box2D/Box2D.h"

#include "Constants.h"

struct ArenaLayoutData
{
    //Lua imported variables.
    float WALL_THICKNESS;
    float WALL_BUFFER;
    std::vector<b2Vec2> P1StartingPositions;
    std::vector<b2Vec2> P2StartingPositions;
    std::vector<std::vector<b2Vec2>> StartingPositions;

    std::vector<b2Vec2> GoalPositions;
    std::vector<b2Vec2> ScoreDisplayPositions;

    //Derivative Variables from the Lua variables.
    //WallSizes
    b2Vec2 TopWallSize; 
    b2Vec2 BottomWallSize;
    b2Vec2 LeftWallSize;
    b2Vec2 RightWallSize;
    std::vector<b2Vec2> WallSizes;
    //GoalWallSizes
    b2Vec2 GoalTopWallSize;
    b2Vec2 GoalBotWallSize;
    b2Vec2 GoalSideWallSize;
    std::vector<b2Vec2> GoalWallSizes;
    b2Vec2 GoalSize; //Factor this out?

    b2Vec2 TopWallPos = {SCREEN_WIDTH/2, 30};
    b2Vec2 BottomWallPos = {SCREEN_WIDTH/2, SCREEN_HEIGHT - 30};
    b2Vec2 LeftWallPos = {30, SCREEN_HEIGHT/2};
    b2Vec2 RightWallPos = {SCREEN_WIDTH-30, SCREEN_HEIGHT/2};
    std::vector<b2Vec2> WallPositions = {TopWallPos, BottomWallPos, LeftWallPos, RightWallPos};

    b2Vec2 Goal1TopWallPos;
    b2Vec2 Goal1BotWallPos;
    b2Vec2 Goal1SideWallPos;
    std::vector<b2Vec2> Goal1WallPositions; 
    
    b2Vec2 Goal2TopWallPos;
    b2Vec2 Goal2BotWallPos;
    b2Vec2 Goal2SideWallPos;
    std::vector<b2Vec2> Goal2WallPositions; 
};


#endif
