#ifndef KEYBIND_DATA_H
#define KEYBIND_DATA_H

#include <vector>
#include <array>

#include "SDL2/SDL.h"


struct KeyBindingData
{
    std::vector<SDL_Keycode> P1SwapKeys = { SDLK_i, 
                                            SDLK_o, 
                                            SDLK_p };

    std::vector<SDL_Keycode> P1DirectionKeys = { SDLK_UP, 
                                              SDLK_DOWN, 
                                              SDLK_LEFT, 
                                              SDLK_RIGHT };
    std::vector<std::vector<SDL_Keycode>> P1Keys = {P1SwapKeys, P1DirectionKeys}; 

    std::vector<SDL_Keycode> P2SwapKeys = { SDLK_v, SDLK_b, SDLK_n };
    std::vector<SDL_Keycode> P2DirectionKeys = { SDLK_w, SDLK_s, SDLK_a, SDLK_d };
    std::vector<std::vector<SDL_Keycode>> P2Keys = {P2SwapKeys, P2DirectionKeys};

    std::vector<std::vector<std::vector<SDL_Keycode>>> Keys = {P1Keys, P2Keys};
};

// struct KeyBindingData
// {
//     std::vector<SDL_Keycode> P1SwapKeys;
//     std::vector<SDL_Keycode> P1DirectionKeys;
//                                       
//     std::vector<std::vector<SDL_Keycode>> P1Keys;
//
//     std::vector<SDL_Keycode> P2SwapKeys;
//     std::vector<SDL_Keycode> P2DirectionKeys;
//     std::vector<std::vector<SDL_Keycode>> P2Keys;
//
//     std::vector<std::vector<std::vector<SDL_Keycode>>> Keys;
// };


#endif
