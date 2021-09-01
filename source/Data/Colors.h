#ifndef COLOR_DATA_H
#define COLOR_DATA_H

#include <vector>

#include "SDL2/SDL.h"


struct PlayerColorData
{
    //Colors specific to each player:
    //  For now, just the selector, but may include Angle Indicator or GoalZone Indicator.
    SDL_Color p1_sel_color;
    SDL_Color p2_sel_color;
};

struct TextColors
{
    SDL_Color timer_color;
    SDL_Color p1_score_color;
    SDL_Color p2_score_color;

};

struct ArenaColorData
{
    SDL_Color outer_wall_color;
    SDL_Color goal_wall_color;
};

#endif
