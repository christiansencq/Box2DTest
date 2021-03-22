#pragma once

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"


class PhysicsEntity
{
public:
	PhysicsEntity(float w, float h, float x, float y, b2World* world, bool dynamic = false);
	~PhysicsEntity();
	
	void Update();
	void Render(SDL_Renderer* renderer);

    b2Body* GetPhysBody() {return mPhysBody; }

private:
	int mWidth, mHeight; //Just for setting up the initial display and such.
	
	float density; // For fixtureDef if Dynamic
	float friction; //For fixtureDef if Dynamic

    b2Body* mPhysBody;
	b2World* physWorld; //UnownedPtr to the physics world.
 
    bool isDynamic; // For bodyDef/fixtureDef

	SDL_Rect mRectangle; //The rectangle that SDL displays over the body.
	SDL_Color mColor;
	SDL_Renderer* renderer;
};
