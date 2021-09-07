#ifndef KEYBIND_DATA_H
#define KEYBIND_DATA_H

#include <vector>
#include <array>

#include "SDL2/SDL.h"


struct KeyBindingData
{
    // std::vector<SDL_Keycode> P1SwapKeys;
    // std::vector<SDL_Keycode> P1DirectionKeys; 
    //
    // std::vector<SDL_Keycode> P2SwapKeys;
    // std::vector<SDL_Keycode> P2DirectionKeys;

    std::vector<std::vector<SDL_Keycode>> P1Keys;
    std::vector<std::vector<SDL_Keycode>> P2Keys;

    std::vector<std::vector<std::vector<SDL_Keycode>>> Keys;
};

#endif
