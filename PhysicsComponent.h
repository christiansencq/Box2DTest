#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "Component.h"
#include "Entity.h"



class PhysicsComponent : public Component
{
public:
    // PhysicsComponent(float x, float y, float w, float h, b2World* world, bool dynamic = false);
    // PhysicsComponent(b2Vec2 physPos, b2Vec2 physSize, b2World* world, bool dynamic = false);
    //PhysicsComponent(int pixelX, int pixelY, int pixelW, int pixelH, b2World* world, bool dynamic);
    PhysicsComponent(b2World* world, bool dynamic);
    PhysicsComponent(b2World* world, bool dynamic, ShapeType shape);
    PhysicsComponent(b2World* world, bool dynamic, std::string name, ShapeType shape);
    ~PhysicsComponent();
    void Initialize(); //Handle the body, shape, fixture creation.
    void CreateBody();
    void MakeCircleShape();
    void MakeRectShape();
    void GenerateFixture(b2Shape* shape);
    void HandleEvents(SDL_Event &event) {}
    void HandleKeyPress(const SDL_Keycode key) {}
    void HandleKeyRelease(const SDL_Keycode key) {}
    void Update();
    void Render(SDL_Renderer* renderer) {}
    void printType() const;

    b2Body* GetPhysBody() { return physBody; }
    bool IsDynamic() const {return isDynamic;}

    void SetThrusting(bool thrusting) { isThrusting = thrusting; }
    void SetThrustingVec(b2Vec2 thrust_vector);
    void SetThrustDirection(ThrustDir dir);
    void SetTurning(TurnDir turning);    

    Entity* owner;

private:

    int PixelX, PixelY;
    int PixelW, PixelH;
    int mRadius;

    float baseThrust;

    bool isThrusting;
    b2Vec2 thrustingVec;
    TurnDir turn;

    float density;
    float friction;
    float angle;

    //This one is not owned.
    b2World* physWorld;//Needed for body creation only.  Could be passed in until CreateBody is called.

    //These are owned.
    b2Body* physBody;
    b2Fixture* physFixture;

    bool isDynamic;
    const std::string type = "PhysicsComponent";
    //std::string shapeType; //Either circle or rect.  Should make this an ENUM
    ShapeType shapeType;
};

#endif