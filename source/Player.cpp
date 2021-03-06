#include "Player.h"
#include "Entity.h"

Player::Player(std::vector<std::vector<SDL_Keycode>> keybind)
 : m_SwapKeys(keybind[0]), m_ActionKeys(keybind[1])
{
    std::cout << "Player constructor where SwapKeys is " << m_SwapKeys.size() << " and ActionKeys is " << m_ActionKeys.size() << " length\n";
}

Player::~Player()
{

}

void Player::AddBallToTeam(Entity* new_entity) 
{ 
    m_TeamsBalls.push_back(new_entity); 
    m_ActiveBall = m_TeamsBalls[0];
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
    if (m_ActiveBall->HasComponent<SelectableComponent>())
    {
        m_ActiveBall->GetComponent<SelectableComponent>()->Deselect();
    }

    m_ActiveBall = m_TeamsBalls[new_ball];
    m_ActiveBall->GetComponent<SelectableComponent>()->Select(); 
}

void Player::RenderSelector(SDL_Renderer* renderer)
{
    m_ActiveBall->GetComponent<SelectableComponent>()->Render();
}

void Player::UpdateSelector()
{
    m_ActiveBall->GetComponent<SelectableComponent>()->Update();
}

void Player::IncrementScore(int num)
{
    m_Score += num;
    std::string new_score = "Player " + std::to_string(id_number+1) + " Score : " + std::to_string(m_Score);

    m_ScoreDisplay->GetComponent<TextComponent>()->SetText(new_score);
}

void Player::ResetPositions()
{
    std::cout << "ResetPositions Start." <<std::endl;
    //Assert that starting Positions have been assigned.
    for (size_t i = 0; i < m_TeamsBalls.size(); i++)
    {
        m_TeamsBalls[i]->ResetTransform();
    }    

    std::cout << "Reset End." <<std::endl;
}

