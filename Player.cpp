#include "Player.h"



Player::Player(std::array<SDL_Keycode, 3> swap_keys, std::array<SDL_Keycode, 4> action_keys)
: m_SwapKeys (swap_keys), m_ActionKeys (action_keys)
{

}

Player::~Player()
{

}

void Player::HandleKeyPress(SDL_Keycode key) 
{
    if (key == m_SwapKeys[0])
    {
        SwapActiveBall(0);
    }
    else if (key == m_SwapKeys[1])
    {
        SwapActiveBall(1);
    }
    else if (key == m_SwapKeys[2])
    {
        SwapActiveBall(2);
    }
    else
    {
        m_ActiveBall->HandleKeyPress(key);
    }
}

void Player::HandleKeyRelease(SDL_Keycode key)
{
    m_ActiveBall->HandleKeyRelease(key);     
}

void Player::SwapActiveBall(int new_ball) 
{
    std::cout << "Old activeBall: " << m_ActiveBall << " -  New activeBall: " << m_TeamsBalls[new_ball] << "\n";
    m_ActiveBall->GetComponent<SelectableComponent>()->Deselect();
    m_ActiveBall = m_TeamsBalls[new_ball];
    m_ActiveBall->GetComponent<SelectableComponent>()->Select(); 
}

void Player::RenderSelector(SDL_Renderer* renderer)
{
    m_ActiveBall->GetComponent<SelectableComponent>()->Render(renderer);
}

void Player::UpdateSelector()
{
    m_ActiveBall->GetComponent<SelectableComponent>()->Update();
}
