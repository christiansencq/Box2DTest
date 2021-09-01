#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include <vector>
#include <cassert>

#include "ScriptLoader.h"
#include "ObjectFactory.h" 
#include "EntityManager.h" 
#include "Player.h" 

//Track information about players, set up players' teams, load data for players, and handle player input.
class PlayerManager
{
public:
    PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena);
    PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena, KeyBindingData& keybind_data);

    void SetUpPlayers(int player_count);
    void ResetPlayers();
    void HandleKeyPresses(SDL_Keycode key);
    void HandleKeyReleases(SDL_Keycode key);

    int GetPlayerCount() const { return player_count; }
    int GetTeamSize() const { return team_size; }
    std::vector<SDL_Color> GetSelColor() { return PlayerSelectorColors; }

    void SetSelectorColors(PlayerColorData& player_sel_colors) { PlayerSelectorColors = { player_sel_colors.p1_sel_color, player_sel_colors.p2_sel_color }; }
    
private:
    ObjectFactory& mObjectFactory;
    ArenaLayoutData& arena;

    std::vector<Player> mPlayers;
    // std::vector<std::shared_ptr<Player>> mPlayers;
    std::vector<std::vector<b2Vec2>> mStartingPositions;
    std::vector<SDL_Color> PlayerSelectorColors;

    KeyBindingData kbdat;
    std::vector<std::vector<std::vector<SDL_Keycode>>> mKeybinds;

    int player_count;
    int team_size = 3;
};

#endif
