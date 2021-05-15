#include "Player.h"
#include "Selector.h"



Player::Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys)
: SwapKeys (swap_keys), ActionKeys (action_keys)
{
    //Delay this until after the std::vector<Entity*> is fully populated.
    //selector = std::make_unique<Selector>(this);
//    selector = new Selector(this);
}

Player::~Player()
{

}

void Player::HandleKeyPress(SDL_Keycode key) 
{
    if (key == SwapKeys[0])
    {
        SwapActiveBall(0);
    }
    else if (key == SwapKeys[1])
    {
        SwapActiveBall(1);
    }
    else if (key == SwapKeys[2])
    {
        SwapActiveBall(2);
    }
    else
    {
        activeBall->HandleKeyPress(key);
    }
}

void Player::HandleKeyRelease(SDL_Keycode key)
{
    activeBall->HandleKeyRelease(key);     
}

// void Player::AddTeam(std::vector<Entity*> ents)
// { for (auto entity: ents)
//          teamsBalls.push_back(entity);
//     activeBall = teamsBalls[0];
//     selector = std::make_unique<Selector>(this); }

void Player::AddSelector()
{

    //selector = new Selector(this);
}

void Player::SwapActiveBall(int new_ball) 
{
    std::cout << "Old activeBall: " << activeBall << " -  New activeBall: " << teamsBalls[new_ball] << "\n";
    activeBall->GetComponent<SelectableComponent>()->Deselect();
    activeBall = teamsBalls[new_ball];
    activeBall->GetComponent<SelectableComponent>()->Select(); 

}

void Player::RenderSelector(SDL_Renderer* renderer)
{
    activeBall->GetComponent<SelectableComponent>()->Render(renderer);
}

void Player::UpdateSelector()
{
    activeBall->GetComponent<SelectableComponent>()->Update();
}