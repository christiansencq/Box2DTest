#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(float w, float h, float x, float y, World* world, bool dynamic)
 : mWidth(w), mHeight(h), physWorld(world->getb2World()), isDynamic(dynamic)
 {
     b2BodyDef bodyDef;
     if (dynamic)
     {
         bodyDef.type = b2_dynamicBody;
     }
     bodyDef.position.Set(x, y);

     b2Body* mPhysBody = physWorld->CreateBody(&bodyDef);
     b2PolygonShape myShape;
     myShape.SetAsBox(w/2.0, h/2.0);

     if (dynamic)
     {
         b2FixtureDef fixtureDef;
         fixtureDef.shape = &myShape;
         fixtureDef.density = 1.0f;
         fixtureDef.friction = 0.3f;
         mPhysBody->CreateFixture(&fixtureDef);
     }
     else
     {
         mPhysBody->CreateFixture(&myShape, 0.0f);
     }
     
     mRectangle.w = w;
     mRectangle.h = h;
     mRectangle.x = x;
     mRectangle.y = y;
 }

 PhysicsEntity::~PhysicsEntity()
 {
    
 }

 void PhysicsEntity::Update()
 {
     //Nothing quite yet.
 }

 void PhysicsEntity::Render(SDL_Renderer* renderer)
 {
     b2Vec2 position = mPhysBody->GetPosition();
     float angle = mPhysBody->GetAngle();

     mRectangle.x = position.x;
     mRectangle.y = position.y;

     SDL_SetRenderDrawColor(renderer, 250, 0, 200, 255);
     SDL_RenderFillRect(renderer, &mRectangle);
}

