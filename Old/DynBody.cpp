#include "DynBody.h"
#include "Constants.h"

DynBody::DynBody(b2World& world) : mWorld(world), xPos(0.0f), yPos(4.0f), w(50.0f), h(10.0f)
{
    b2BodyDef dynamicBodyDef;
    dynamicBodyDef.position.Set(xPos, yPos);
    mBody = mWorld.CreateBody(&dynamicBodyDef);

    b2PolygonShape mBox;
    mBox.SetAsBox(w, h);

    b2FixtureDef dynFixtureDef;
    dynFixtureDef.shape = &mBox;
    dynFixtureDef.density = 1.0f;
    dynFixtureDef.friction = 0.3f;

    mBody->CreateFixture(&dynFixtureDef);
}

DynBody::~DynBody() 
{
    mWorld.DestroyBody(mBody);   
}

void DynBody::update()
{
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = mBody->GetPosition();
    float angle = mBody->GetAngle(); 

    printf("X, Y, Angle: %4.2f %4.2f %4.2f\n", position.x, position.y, angle);
}