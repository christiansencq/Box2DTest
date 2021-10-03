#include "PlayerOwnerComponent.h"
#include <iostream>


PlayerOwnerComponent::PlayerOwnerComponent(Player* player)
    : mPlayer(player)
{
    std::cout << "[POComp] Player Id " << mPlayer->GetPlayerID() << "\n\n";

}
