#include "Box2D/Box2D.h"

struct aBody 
{
    b2BodyDef DEF;
    b2PolygonShape SHAPE;
    b2FixtureDef FIX;
    b2Body* BOD;
    //sf::rectangleshape rect; - Change to an SDL rect?
};

class PhysBody
{
    //A rectangular body that has physics.
public:
    PhysBody(b2World* world);

    void setSelfPhysics();
private:
    float xpos, ypos;
    float halfWidth;
    float halfHeight;
    b2World* mWorld;
    aBody* myBody;
};