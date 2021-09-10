#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include <iostream>
#include <memory>
#include <bitset>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "../Data/Constants.h"
#include "Component.h"

class Entity;


struct CollisionData 
{
    bool isSensor = false;
    bool isScorer = false;
};

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(b2World* world, ShapeType shape, b2BodyType body_type);
    ~PhysicsComponent();
    virtual void Initialize() override; 
    virtual void Update() override;

    b2Body* GetPhysBody() { return m_PhysBody; }
    b2BodyType GetBodyType() { return m_PhysBody->GetType(); }

    void SetThrusting(bool thrusting) { isThrusting = thrusting; }
    void SetThrustDirection(ThrustDir dir);
    void SetFixedTurning(TurnDir turning, bool fixed);  
    void SetTurning(TurnDir turning);    
    void SetTransform(b2Vec2 pos, float angle);

    void SetData(bool scorer = false);

    Entity* GetOwner() const { return owner; }
    Entity* owner;

private:
    void MakeCircleShape(float x_offset, float y_offset);
    void MakeRectShape();
    void GenerateFixture(b2Shape* shape);
    void CreateBody();

    //In the same way that width/height were moved to the Entity. rad should too.
    int m_Radius;

    bool isThrusting = false;
    b2Vec2 m_ThrustingVec;
    TurnDir m_Turn = TurnDir::NONE;
    
    float m_TurnSpeed = 0.01;//Lower value is slower turn. 
    float m_Density = 0.1;
    float m_Friction = 0.1;
    float m_Angle;
    bool m_IsSensor;

    b2World* m_PhysWorld;//Needed for body creation only.  Could be passed in until CreateBody is called.

    b2Body* m_PhysBody;
    b2Fixture* m_PhysFixture;
    ShapeType m_ShapeType;
    b2BodyType m_BodyType;

    CollisionData m_CollisionData;
    
    const std::string type = "PhysicsComponent";
};

#endif
