#include "ObjectFactory.h"
#include "Components/GoalZoneComponent.h"
#include "Components/PhysicsComponent.h"

ObjectFactory::ObjectFactory(SDL_Renderer* renderer, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<EntityManager> entityManager, b2World* physWorld) : m_Renderer(renderer), m_AssetManager(assetManager), m_EntityManager(entityManager), m_PhysicsWorld(physWorld)
{

}

void ObjectFactory::CreateOuterWalls(std::vector<b2Vec2> positions, std::vector<b2Vec2> sizes)
{
    for (size_t i = 0; i < positions.size(); i++)
    {
        Entity* wall = m_EntityManager->AddEntity(positions[i], sizes[i]);
        wall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
        wall->GetComponent<PhysicsComponent>()->SetData(false);
        wall->AddComponent<SDLRectComponent>(m_Renderer);
    }

    for (size_t i = 0; i < positions.size(); i++)
    {
        Entity* wall = m_EntityManager->AddEntity(positions[i], sizes[i]);
        wall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
        wall->GetComponent<PhysicsComponent>()->SetData(false);
        wall->AddComponent<SDLRectComponent>(m_Renderer);
    }
}

void ObjectFactory::CreateGoalWalls(std::vector<b2Vec2> wallPositions, std::vector<b2Vec2> wallSizes)
{
    //Assert wallPositions.size() == wallSizes.size()
    for (size_t i = 0; i < wallPositions.size(); i++)
    {
        Entity* GoalWall = m_EntityManager->AddEntity(wallPositions[i], wallSizes[i]);
        GoalWall->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::RECT, b2BodyType::b2_staticBody);
        GoalWall->GetComponent<PhysicsComponent>()->SetData(false);
        GoalWall->AddComponent<SDLRectComponent>(m_Renderer);
    }
}

Entity* ObjectFactory::CreatePuck(b2Vec2 startPos)
{
    Entity* puck = m_EntityManager->AddEntity(startPos, 25.0f);
    puck->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody);
    puck->GetComponent<PhysicsComponent>()->SetData(true);
    puck->AddComponent<SDLCircleComponent>(m_Renderer, GREEN);

    return puck;
}

Entity* ObjectFactory::CreatePlayerBall(std::shared_ptr<Player> player, b2Vec2 startPos, SDL_Color sel_color)
{
    std::cout << "Creating Player Ball at " << startPos.x << " " << startPos.y << "\n";

    Entity* ball = m_EntityManager->AddEntity(startPos, 50.0f);
    std::cout << "Entity made; Adding to Team\n";
    player->AddBallToTeam(ball);
    std::cout << "Adding Components\n";
    ball->AddComponent<PhysicsComponent>(m_PhysicsWorld, ShapeType::CIRCLE, b2BodyType::b2_dynamicBody);
    ball->GetComponent<PhysicsComponent>()->SetData(false);
    ball->AddComponent<SDLCircleComponent>(m_Renderer);
    ball->AddComponent<SelectableComponent>(m_Renderer, sel_color);
    ball->AddComponent<KeyInputComponent>(player->GetActionKeys());
    ball->GetComponent<KeyInputComponent>()->AddCommand<ForwardThrustCommand>();
    ball->GetComponent<KeyInputComponent>()->AddCommand<BackwardThrustCommand>();
    ball->GetComponent<KeyInputComponent>()->AddCommand<LeftTurnCommand>();
    ball->GetComponent<KeyInputComponent>()->AddCommand<RightTurnCommand>();

    std::cout << "Done with Ball.\n";
    return ball;
}

Entity* ObjectFactory::CreateGoalZone(std::shared_ptr<Player> player, b2Vec2 position, b2Vec2 size)
{
    Entity* goal_zone = m_EntityManager->AddEntity(position, size);
    goal_zone->AddComponent<GoalZoneComponent>(m_PhysicsWorld, player);
    goal_zone->GetComponent<GoalZoneComponent>()->SetData(false);

    return goal_zone;
}

Entity* ObjectFactory::CreateScoreDisplay(std::shared_ptr<Player> player, b2Vec2 position, b2Vec2 size)
{
    Entity* score_display = m_EntityManager->AddEntity(position, size);
    score_display->AddComponent<TextComponent>(m_AssetManager, m_Renderer, "Player " + std::to_string(player->id_number+1) + " Score : " + std::to_string(0), "ScoreFont");
    player->AddScoreDisplay(score_display);

    return score_display;
}
