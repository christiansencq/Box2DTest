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
    // PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena_data);
    PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena_data, KeyBindingData& keybind_data);
    // PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena_data, KeyBindingData& keybind_data, PlayerColorData& color_data);

    void SetUpPlayers(PlayerColorData& color, int player_count);
    void ResetPlayers();
    void HandleKeyPresses(SDL_Keycode key);
    void HandleKeyReleases(SDL_Keycode key);

    int GetPlayerCount() const { return player_count; }
    int GetTeamSize() const { return team_size; }
    std::vector<SDL_Color> GetSelColor() { return PlayerSelectorColors; }

    
private:

    void SetPlayerColors(PlayerColorData& player_colors) {
        PlayerSelectorColors = {player_colors.p1_sel_color, player_colors.p2_sel_color};
        PlayerScoreColors = {player_colors.p1_score_color, player_colors.p2_score_color};
    }
    ObjectFactory& mObjectFactory;
    ArenaLayoutData& mArena;
    std::vector<std::vector<std::vector<SDL_Keycode>>> mKeybinds;
    // PlayerColorData& mColors;

    std::vector<Player> mPlayers;
    std::vector<std::vector<b2Vec2>> mStartingPositions;
    std::vector<SDL_Color> PlayerSelectorColors;
    std::vector<SDL_Color> PlayerScoreColors;


    // KeyBindingData kbdat;

    int player_count = 2;
    int team_size = 3;
};

#endif
