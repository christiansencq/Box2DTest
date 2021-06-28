#include "Box2D/Box2D.h"
//#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactManager : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); 

private:


};
