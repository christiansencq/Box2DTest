#include "PlayerManager.h"

PlayerManager::PlayerManager(std::shared_ptr<ObjectFactory> object_factory, ArenaLayoutData& arena)
    : mObjectFactory(object_factory), arena(arena)
{

}

PlayerManager::PlayerManager(std::shared_ptr<ObjectFactory> object_factory, ArenaLayoutData& arena, KeyBindingData& keybind_data)
    : mObjectFactory(object_factory), arena(arena), mKeybinds(keybind_data.Keys)
{
    // kbdat = KeyBindingData();
    
    mKeybinds = kbdat.Keys;
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

void PlayerManager::SetUpPlayers(int player_count)
{
    // assert((player_count != static_cast<int>(mStartingPositions.size())) && "Num of StartingPosition lists != NumPlayers");
    // assert((player_count != static_cast<int>(mKeybinds.size())) && "Num of keybinds != Num Players");
    mStartingPositions = arena.StartingPositions;

    for (int i = 0; i < player_count; i++)
    {
        std::shared_ptr<Player> player = std::make_shared<Player>(mKeybinds[i]);
        std::cout << "Player " << std::to_string(i+1) << " made. \n";

        player->id_number = i;

        std::cout << "Adding starting positions \n";
        player->AddStartingPositions(mStartingPositions[i]);

        std::cout << "Making player balls \n";
        for (int j = 0; j < team_size; j++)
        {
            std::cout << "Pos x " << mStartingPositions[i][j].x << "  " << mStartingPositions[i][j].y << "\n";
            mObjectFactory->CreatePlayerBall(player, mStartingPositions[i][j], PlayerSelectorColors[i] );
        }

        std::cout << "Making score display \n";
        mObjectFactory->CreateScoreDisplay(player, arena.ScoreDisplayPositions[i], arena.GoalSize);

        std::cout << "Making goal zone\n";
        mObjectFactory->CreateGoalZone(player, arena.GoalPositions[i], arena.GoalSize);

        player->SwapActiveBall(0);
        
        mPlayers.push_back(player);
        std::cout << "Player " << std::to_string(i+1) << " made. \n";
    }
}
