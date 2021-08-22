#ifndef COLOR_DATA_H
#define COLOR_DATA_H

#include <vector>

#include "SDL2/SDL.h"


struct PlayerColorData
{
    SDL_Color selector_color;
    SDL_Color score_display_color;
    SDL_Color goal_zone_color;
};


struct BallColorData
{
    //Not implemented at this time, just a reminder of the function of this header.
};

struct ArenaColorData
{

    SDL_Color outer_wall_color;
    SDL_Color goal_wall_color;


};

#endif
