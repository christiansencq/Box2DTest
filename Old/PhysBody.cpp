#include "PhysBody.h"

PhysBody::PhysBody(b2World* world) : mWorld(world), halfWidth(50.0f), halfHeight(10.0f)
{
    myBody = new aBody();
}

PhysBody::~PhysBody()
{
    delete myBody;
}

void PhysBody::setSelfPhysics()
{
    myBody->SHAPE.SetAsBox(50.0f, 10.0f);
    myBody->FIX.shape = &myBody->SHAPE;

    myBody->BOD = mWorld->CreateBody(&myBody->DEF)  ;
    myBody->BOD->CreateFixture(&myBody->SHAPE, 1.0f);
}