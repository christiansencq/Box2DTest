#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"

#include "Constants.h"
#include "Component.h"
#include "Entity.h"

class PhysicsComponent : public Component
{
public:
    // PhysicsComponent(float x, float y, float w, float h, b2World* world, bool dynamic = false);
    // PhysicsComponent(b2Vec2 physPos, b2Vec2 physSize, b2World* world, bool dynamic = false);
    PhysicsComponent(int pixelX, int pixelY, int pixelW, int pixelH, b2World* world, bool dynamic);
    PhysicsComponent(int pixelX, int pixelY, int pixelR, b2World* world, bool dynamic);
    ~PhysicsComponent();
    void Initialize();
    void HandleEvents(SDL_Event &event) {}
    void HandleKeyPress(const SDL_Keycode key);
    void HandleKeyRelease(const SDL_Keycode key);
    void Update();
    void Render(SDL_Renderer* renderer);
    void printType() const;

    b2Body* GetPhysBody() { return physBody; }
    bool IsDynamic() {return isDynamic;}

    void SetThrusting(bool thrusting) { isThrusting = thrusting; }
    void SetTurning(TurnDir turning) { turn = turning; }    

    Entity* owner;


private:
//    Entity* owner;

    int PixelX, PixelY;
    int PixelW, PixelH;
    int PixelR;

    bool isThrusting;
    TurnDir turn;

    float mPhysX; //Used for initialization.
    float mPhysY;
    float mWidth; //Used in initialization.
    float mHeight;

    float density;
    float friction;
    float angle;


    //This one is not owned.
    b2World* physWorld;

    //These are owned.
    b2Body* physBody;
    b2Fixture* physFixture;
    //b2PolygonShape* shape;

    //SDLRectComponent* rectComp; //Set to owner->GetComponent<SDLRectComponent>();

    bool isDynamic;
    const std::string type = "PhysicsComponent";
    std::string shapeType; //Either circle or rect.

};

#endif