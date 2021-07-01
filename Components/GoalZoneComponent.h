#ifndef GOAL_ZONE_COMPONENT_H
#define GOAL_ZONE_COMPONENT_H

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include <iostream>
#include <memory>

#include "../Constants.h"
#include "Component.h"

#include "../Player.h"
#include "PhysicsComponent.h"
//#include "../Entity.h"

//GoalZone has a RectanglePhysicsObject, and a Player to update when Triggered.
//TODO: Integrate the Physics portion into PhysicsComponent and have this be a go-between.

class Entity;

class GoalZoneComponent : public Component
{
public:
    GoalZoneComponent(b2World* world, std::shared_ptr<Player> player);
    ~GoalZoneComponent();

    virtual void Initialize() override;
    virtual void HandleEvents(SDL_Event &event) override {}
    virtual void Update() override;
    virtual void Render() override {}

    void CreateBody();
    void CreateRectShape();
    void GenerateFixture(b2Shape* shape);
    void Score();
    void SetData(bool scorer = false);


    Entity* GetOwner() {return owner;} 
    Entity* owner;

private:
    int m_Width, m_Height;
    bool m_Triggered;
    std::shared_ptr<Player> m_Player;
    b2World* m_PhysWorld;
    b2Body* m_PhysBody;
    BodyData* m_BodyData;
};

#endif
