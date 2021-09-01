#include "PlayerManager.h"

PlayerManager::PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena_data, KeyBindingData& keybind_data)
    : mObjectFactory(object_factory), mArena(arena_data), mKeybinds(keybind_data.Keys) 
// PlayerManager::PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena_data, KeyBindingData& keybind_data, PlayerColorData& color_data)
//     : mObjectFactory(object_factory), mArena(arena_data), mKeybinds(keybind_data.Keys), mColors(color_data)
{

}

void PlayerManager::HandleKeyPresses(SDL_Keycode key)
{
    for (auto& player : mPlayers)
    {
        player.HandleKeyPress(key);
    }
}

void PlayerManager::HandleKeyReleases(SDL_Keycode key)
{
    for (auto& player : mPlayers)
    {
        player.HandleKeyRelease(key);
    }
}

void PlayerManager::ResetPlayers()
{
    for (auto& player : mPlayers)
    {
        player.ResetPositions();
    }
}

void PlayerManager::SetUpPlayers(PlayerColorData& color, int player_count)
// void PlayerManager::SetUpPlayers(int player_count)
{
    // assert((player_count == static_cast<int>(mStartingPositions.size())) && "Num of StartingPosition lists != NumPlayers");
    // assert((player_count == static_cast<int>(mKeybinds.size())) && "Num of keybinds != Num Players");
    std::cout << "Setting up players\n";

    mStartingPositions = mArena.StartingPositions;
    std::cout << "Set up starting positions\n";

    SetPlayerColors(color);
    // PlayerSelectorColors = { color.p1_sel_color, color.p2_sel_color };
    // PlayerScoreColors = { color.p1_score_color, color.p2_score_color };

    for (int i = 0; i < player_count; i++)
    {
        std::cout << "Making Player " << std::to_string(i+1) << ". \n";
        Player player = Player{i, mKeybinds[i]};

        player.AddStartingPositions(mStartingPositions[i]);

        for (int j = 0; j < team_size; j++)
        {
            std::cout << "Pos x " << mStartingPositions[i][j].x << "  " << mStartingPositions[i][j].y << "\n";
            mObjectFactory.CreatePlayerBall(player, mStartingPositions[i][j], PlayerSelectorColors[i] );
        }

        std::cout << "Making score display \n";


        mObjectFactory.CreateScoreDisplay(player, mArena.ScoreDisplayPositions[i], mArena.GoalSize, color.score_colors[i]);

        std::cout << "Making goal zone\n";
        mObjectFactory.CreateGoalZone(player, mArena.GoalPositions[i], mArena.GoalSize);

        player.SwapActiveBall(0);
        mPlayers.push_back(player);
        
        std::cout << "Player " << std::to_string(i+1) << " made. \n";
    }
}
