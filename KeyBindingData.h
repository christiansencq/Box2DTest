#ifndef KEYBIND_DATA_H
#define KEYBIND_DATA_H

#include <vector>
#include <array>

#include "SDL2/SDL.h"

// struct KeyBind
// {
//     std::vector<SDL_Keycode> SwapKeys = { SDLK_i, SDLK_o, SDLK_p };
//     std::vector<SDL_Keycode> ActionKeys = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
//     std::vector<std::vector<SDL_Keycode>> Keys = {SwapKeys, ActionKeys}; 
// };
//
struct KeyBindingData
{
    std::vector<SDL_Keycode> P1SwapKeys = { SDLK_i, SDLK_o, SDLK_p };
    std::vector<SDL_Keycode> P1ActionKeys = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
    std::vector<std::vector<SDL_Keycode>> P1Keys = {P1SwapKeys, P1ActionKeys}; 

    std::vector<SDL_Keycode> P2SwapKeys = { SDLK_v, SDLK_b, SDLK_n };
    std::vector<SDL_Keycode> P2ActionKeys = { SDLK_w, SDLK_s, SDLK_a, SDLK_d };
    std::vector<std::vector<SDL_Keycode>> P2Keys = {P2SwapKeys, P2ActionKeys};

    std::vector<std::vector<std::vector<SDL_Keycode>>> Keys = {P1Keys, P2Keys};
};


#endif
