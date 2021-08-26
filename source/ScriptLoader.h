#ifndef SCRIPT_LOADER_H
#define SCRIPT_LOADER_H

#include <iostream>
#include <string>
#include <vector>

#include <lua.hpp>
#include <sol/sol.hpp>

#include "Box2D/Box2D.h"

#include "Colors.h"
#include "ArenaLayout.h"

#include "Player.h"

class ScriptLoader
{
public:
    ScriptLoader();
    ~ScriptLoader();

    void SolLoadArenaData(std::string arena_data_file, ArenaLayoutData& arena);

    void LoadPlayerSelectorColors(const char* color_data_file, PlayerColorData& color);

private:
    void LoadSingleColor(SDL_Color& color, const std::vector<int>& cvec);
    void CalcArenaData(ArenaLayoutData& arena);
};

#endif
