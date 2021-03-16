#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"
#include "BoxWorld.h"

class PhysicsEntity
{
public:
	PhysicsEntity(float w, float h, float x, float y, World* world, bool dynamic = false);
	~PhysicsEntity();
	
	void Update();
	void Render(SDL_Renderer* renderer);

private:
	int mWidth, mHeight; //Just for setting up the initial display and such.
	
	bool isDynamic; // For bodyDef/fixtureDef
	float density; // For fixtureDef if Dynamic
	float friction; //For fixtureDef if Dynamic

	b2Body* mPhysBody; //The physical body, everything needed for the physics.
	b2World* physWorld; //UnownedPtr to the physics world.
		
	SDL_Rect mRectangle; //The rectangle that SDL displays over the body.
	SDL_Color mColor;
	SDL_Renderer* renderer;
	
};
