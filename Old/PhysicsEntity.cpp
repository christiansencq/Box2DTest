#include "PhysicsEntity.h"
#include <iostream>

PhysicsEntity::PhysicsEntity(float w, float h, float x, float y, b2World* world, bool dynamic)
 : mWidth(w), mHeight(h), physWorld(world), isDynamic(dynamic)
 {
     b2BodyDef bodyDef;
     if (dynamic)
     {
         bodyDef.type = b2_dynamicBody;
     }
     bodyDef.position.Set(x, y);

     mPhysBody = physWorld->CreateBody(&bodyDef);
     
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
     std::cout << "X " << mPhysBody->GetPosition().x << "\n";
     std::cout << "Y " << mPhysBody->GetPosition().y << "\n";
     mRectangle.w = w;
     mRectangle.h = h;
     mRectangle.x = x;
     mRectangle.y = y;
 }

 PhysicsEntity::~PhysicsEntity()
 {
    physWorld->DestroyBody(mPhysBody);
 }

 void PhysicsEntity::Update()
 {
     //Nothing quite yet.
 }

 void PhysicsEntity::Render(SDL_Renderer* renderer)
 {
     std::cout << "X " << mPhysBody->GetPosition().x << "\n";
     std::cout << "Y " << mPhysBody->GetPosition().y << "\n";
     //float angle = mPhysBody->GetAngle();
     //printf("Pos", position.x, " ", position.y, "\n");

     SDL_SetRenderDrawColor(renderer, 250, 0, 200, 255);
     SDL_RenderFillRect(renderer, &mRectangle);
}

