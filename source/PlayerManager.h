#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include <vector>
#include <cassert>

#include "ArenaLayout.h" //To figure out placement of Balls.
#include "KeyBindingData.h" //To get KeybindData 

#include "ScriptLoader.h"
#include "ObjectFactory.h" //To add entities to Player Teams
#include "EntityManager.h" 
#include "Player.h" //TO add the players and track them.


//Track information about players, set up players' teams, load data for players, and handle player input.
class PlayerManager
{
public:
    PlayerManager(std::shared_ptr<ObjectFactory> object_factory, ArenaLayoutData& arena);

    void SetUpPlayers(int player_count);
    void ResetPlayers();
    void HandleKeyPresses(SDL_Keycode key);
    void HandleKeyReleases(SDL_Keycode key);

    int GetPlayerCount() const { return player_count; }
    int GetTeamSize() const { return team_size; }
    // std::vector<std::vector<int>> GetSelColor() { return PlayerSelectorColors; }
    std::vector<SDL_Color> GetSelColor() { return PlayerSelectorColors; }

    void SetSelectorColors(PlayerColorData& player_sel_colors) { PlayerSelectorColors = { player_sel_colors.p1_sel_color, player_sel_colors.p2_sel_color }; }
    // void SetSelectorColors(const std::vector<std::vector<int>>& player_sel_colors) { PlayerSelectorColors = player_sel_colors; }
    
private:
    std::shared_ptr<ObjectFactory> mObjectFactory;
    ArenaLayoutData& arena;

    std::vector<std::shared_ptr<Player>> mPlayers;
    std::vector<std::vector<b2Vec2>> mStartingPositions;
    std::vector<SDL_Color> PlayerSelectorColors;
    // std::vector<std::vector<int>> PlayerSelectorColors;

    KeyBindingData kbdat;
    std::vector<std::vector<std::vector<SDL_Keycode>>> mKeybinds;

    int player_count;
    int team_size = 3;
};

#endif
