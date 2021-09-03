#ifndef GOAL_ZONE_COMPONENT_H
#define GOAL_ZONE_COMPONENT_H

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include <iostream>
#include <memory>

#include "../Data/Constants.h"
#include "Component.h"
#include "../Player.h"
#include "PhysicsComponent.h"

//GoalZone has a RectanglePhysicsObject, and a Player to update when Triggered.

class Entity;
class GoalZoneComponent : public Component
{
public:
    GoalZoneComponent(b2World* world, Player* player);
    ~GoalZoneComponent();

    virtual void Initialize() override;
    virtual void Update() override;

    void Score();
    void SetData(bool scorer = false);

    void SetIdPlayer(int id) { mIdPlayer = id; }
    Entity* GetOwner() {return owner;} 
    Entity* owner;

private:
    void GenerateFixture(b2Shape* shape);
    void CreateBody();
    void CreateRectShape();

    int mIdPlayer;
    int m_Width, m_Height;
    b2World* m_PhysWorld;
    b2Body* m_PhysBody;
    CollisionData m_CollisionData;
    Player* m_Player;
};

#endif
