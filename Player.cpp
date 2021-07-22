#include "Player.h"
#include "Entity.h"

Player::Player(const std::array<SDL_Keycode, 3> swap_keys, const std::array<SDL_Keycode, 4> action_keys)
 : m_SwapKeys (swap_keys), m_ActionKeys (action_keys)
{

}

Player::Player(const std::array<SDL_Keycode, 3> swap_keys, const std::array<SDL_Keycode, 4> action_keys, Entity* score_display)
 : m_ScoreDisplay(score_display), m_SwapKeys (swap_keys), m_ActionKeys (action_keys) 
{

}

Player::Player(const std::array<SDL_Keycode, 3> swap_keys, const std::array<SDL_Keycode, 4> action_keys, Entity* score_display, std::vector<b2Vec2> starting_pos)
: m_StartingPositions(starting_pos), m_ScoreDisplay(score_display), m_SwapKeys (swap_keys), m_ActionKeys (action_keys) 
{
    //Set the Starting Angle

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
    if (m_ActiveBall)
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

void Player::AddScoreDisplay(Entity* score_disp)
{
    m_ScoreDisplay = score_disp;
}


void Player::IncrementScore(int num)
{
    m_Score += num;
    std::string new_score = "Player Score" + std::to_string(m_Score);

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

