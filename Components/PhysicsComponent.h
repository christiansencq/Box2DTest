#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include <iostream>
#include <memory>
#include <bitset>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "../Constants.h"
#include "Component.h"

class Entity;

//Separate out into : Collision, PhysBodyCommand, similar?

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(b2World* world, ShapeType shape, b2BodyType body_type, isSensor is_sensor);
//    PhysicsComponent(b2World* world, ShapeType shape, b2BodyType body_type, isSensor is_sensor, std::bitset<16> col_cat, std::bitset<16> col_mask);
    ~PhysicsComponent();
    virtual void Initialize() override; //Handle the body, shape, fixture creation.
    virtual void Update() override;
    void CreateBody();
    void MakeCircleShape(float x_offset, float y_offset);
    void MakeRectShape();
    void SetCollisionCategory(std::bitset<16> category) { m_CollisionCategory = category; }
    void SetCollisionMask(std::bitset<16> mask) { m_CollisionMask = mask; }
    void GenerateFixture(b2Shape* shape);

    b2Body* GetPhysBody() { return m_PhysBody; }
    b2BodyType GetBodyType() { return m_PhysBody->GetType(); }

    void SetThrusting(bool thrusting) { isThrusting = thrusting; }
    void SetThrustingVec(b2Vec2 thrust_vector);
    void SetThrustDirection(ThrustDir dir);
    void SetFixedTurning(TurnDir turning, bool fixed);  
    void SetTurning(TurnDir turning);    
    void SetTransform(b2Vec2 pos, float angle);

    Entity* GetOwner() { return owner; }
    Entity* owner;

private:
    //In the same way that width/height were moved to the Entity. rad should too.
    int m_Radius;
    //int m_Width, m_Height;

    bool isThrusting = false;
    b2Vec2 m_ThrustingVec;
    TurnDir m_Turn = TurnDir::NONE;
    
    float m_TurnSpeed = 0.01;//Lower value is slower turn. 
    float m_Density = 0.1;
    float m_Friction = 0.1;
    float m_Angle;

    b2World* m_PhysWorld;//Needed for body creation only.  Could be passed in until CreateBody is called.
    b2Body* m_PhysBody;
    b2Fixture* m_PhysFixture;
    ShapeType m_ShapeType;
    b2BodyType m_BodyType;
    isSensor m_IsSensor;

    //Collision.  Assigned when fixture is. 
    std::bitset<16> m_CollisionCategory;
    std::bitset<16> m_CollisionMask;
    uint16_t m_colCategory;
    uint16_t m_colMask;


    const std::string type = "PhysicsComponent";
};

#endif
