#include "PlayerManager.h"

PlayerManager::PlayerManager(ObjectFactory& object_factory, ArenaLayoutData& arena_data, KeyBindingData& keybind_data)
    : mObjectFactory(object_factory), mArena(arena_data), mKeybinds(keybind_data.Keys) 
{

}

PlayerManager::~PlayerManager()
{

    for (auto p : mPlayers)
    {
        delete p;
    }
}

void PlayerManager::HandleKeyPresses(SDL_Keycode key)
{
    for (auto& player : mPlayers)
    {
        player->HandleKeyPress(key);
    }
}

void PlayerManager::HandleKeyReleases(SDL_Keycode key)
{
    for (auto& player : mPlayers)
    {
        player->HandleKeyRelease(key);
    }
}

void PlayerManager::ResetPlayers()
{
    for (auto& player : mPlayers)
    {
        player->ResetPositions();
    }
}

void PlayerManager::SetUpPlayers(PlayerColorData& color, int player_count)
{
    // assert((player_count == static_cast<int>(mStartingPositions.size())) && "Num of StartingPosition lists != NumPlayers");
    // assert((player_count == static_cast<int>(mKeybinds.size())) && "Num of keybinds != Num Players");
    std::cout << "Setting up players\n";

    mStartingPositions = mArena.StartingPositions;
    std::cout << "Set up starting positions\n";

    SetPlayerColors(color);

    for (int i = 0; i < player_count; i++)
    {
        std::cout << "Making Player " << std::to_string(i+1) << ". \n";
        mPlayers.push_back(new Player(i, mKeybinds[i]));
        mPlayers[i]->AddStartingPositions(mStartingPositions[i]);
        mPlayers[i]->SetScore(0);

        for (int j = 0; j < team_size; j++)
        {
            std::cout << "Pos x " << mStartingPositions[i][j].x << "  " << mStartingPositions[i][j].y << "\n";
            mObjectFactory.CreatePlayerBall(mPlayers[i], mStartingPositions[i][j], PlayerSelectorColors[i] );
        }

        std::cout << "Making score display \n";
        mObjectFactory.CreateScoreDisplay(mPlayers[i], mArena.ScoreDisplayPositions[i], mArena.GoalSize, color.score_colors[i]);
        std::cout << "Making goal zone\n";
        mObjectFactory.CreateGoalZone(mPlayers[i], mArena.GoalPositions[i], mArena.GoalSize);
        
        mPlayers[i]->SwapActiveBall(0);
        std::cout << "[PlMan]Player " << std::to_string(i+1) << " made. \n";
        std::cout << "[PlMan]Player score " << mPlayers[i]->GetScore() << "\n";
        std::cout << "[PlMan]PlayerId " << mPlayers[i]->GetPlayerID() << "\n\n\n";
    }
}
