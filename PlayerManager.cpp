#include "PlayerManager.h"

PlayerManager::PlayerManager(std::shared_ptr<EntityFactory> entity_factory, ArenaLayoutData& arena)
    : mObjectFactory(entity_factory), arena(arena)
{
    kbdat = KeyBindingData();
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
    assert((player_count != static_cast<int>(mStartingPositions.size())) && "Num of StartingPosition lists != NumPlayers");
    assert((player_count != static_cast<int>(mKeybinds.size())) && "Num of keybinds != Num Players");
    mStartingPositions = arena.StartingPositions;

    std::cout << "mStartingPos.length " << mStartingPositions.size() << "\n";
    std::cout << "mStartingPos[0].length " << mStartingPositions[0].size() << "\n";

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
            mObjectFactory->CreatePlayerBall(player, mStartingPositions[i][j]);
        }

        std::cout << "Making score display \n";
        mObjectFactory->CreateScoreDisplay(player, m_EntityFactory->GetArena().ScoreDisplayPositions[i], m_EntityFactory->GetArena().GoalSize);
        std::cout << "Making goal zone\n";
        mObjectFactory->CreateGoalZone(player, m_EntityFactory->GetArena().GoalPositions[i], m_EntityFactory->GetArena().GoalSize);

        player->SwapActiveBall(0);
        
        mPlayers.push_back(player);
        std::cout << "Player " << std::to_string(i+1) << " made. \n";
    }
}
