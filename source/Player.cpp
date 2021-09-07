#include "Player.h"
#include "Entity.h"
#include "Components/TextComponent.h"

Player::Player(int id_num, std::vector<std::vector<SDL_Keycode>> keybind)
 : id_number(id_num), m_SwapKeys(keybind[0]), m_ActionKeys(keybind[1]), m_Score(0)
{
    std::cout << "[Pl]Player constructor\n";
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

void Player::IncrementScore()
{
    std::cout << "[Pl]Incrementing Score.\n";
    this->m_Score += 1;

    int display_id = id_number+1;
    std::cout << "[Pl]New m_Score : " << m_Score << " for Player " << display_id << "\n";
    std::string new_score = ("Player " + std::to_string(display_id) + " Score : " + std::to_string(m_Score));

    m_ScoreDisplay->GetComponent<TextComponent>()->SetText(new_score);

    std::cout << "[Pl]Updated Score display.\n";
}

void Player::ResetPositions()
{
    std::cout << "[Pl]ResetPositions Start." <<std::endl;
    //Assert that starting Positions have been assigned.
    for (size_t i = 0; i < m_TeamsBalls.size(); i++)
    {
        m_TeamsBalls[i]->ResetTransform();
    }    

    std::cout << "[Pl]Reset End." <<std::endl;
}

