#include "StatBody.h"

StatBody::StatBody(b2World& world) : mnoptrWorld(world), xPos(0.0f), yPos(-10.0f), w(50.0f), h(10.0f)
{
    b2BodyDef staticBodyDef;
    staticBodyDef.position.Set(xPos, yPos);
    mStaticBody = mnoptrWorld.CreateBody(&staticBodyDef);
    b2PolygonShape staticRectPolygon;
    staticRectPolygon.SetAsBox(w, h);
    mStaticBody->CreateFixture(&staticRectPolygon, 0.0f);
}

StatBody::~StatBody() 
{

}