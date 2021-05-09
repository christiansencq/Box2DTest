#include "SDLRectComponent.h"


SDLRectComponent::SDLRectComponent(SDL_Renderer* renderer, SDL_Color color) 
 : mnorenderer(renderer), mColor(color)
{

}

void SDLRectComponent::Initialize()
{
  mWidth = owner->GetPixelSize().x;
  mHeight = owner->GetPixelSize().y;
  mPixelX = owner->GetPixelPos().x;
  mPixelY = owner->GetPixelPos().y;

//  physicsComp = owner->GetComponent<PhysicsComponent>()->GetPhysBody();
  mPhysBody = owner->GetComponent<PhysicsComponent>()->GetPhysBody();

  IsDynamic = owner->GetComponent<PhysicsComponent>()->IsDynamic();

}

void SDLRectComponent::Update() 
{

  //Check if not static?
  if (IsDynamic)
  {
    mPixelX = owner->GetPixelPos().x;
    mPixelY = owner->GetPixelPos().y;
  }

}

void SDLRectComponent::Render(SDL_Renderer* renderer) 
{
  //Set colors in here before .
  SDL_SetRenderDrawColor(mnorenderer, mColor.r, mColor.g, mColor.b, mColor.a);
  // Draw a rect here.   
  DisplayRect();

  //Move DisplayAngleIndicator() here?
//  SDL_SetRenderDrawColor(mnorenderer, 200, 50, 50, 255);
  // if (IsDynamic)
  // {
  //   DisplayAngleIndicator();
  // }
}

void SDLRectComponent::DisplayRect()
{
  //Breaks down the PhysicsBody into a set of vertices that we can draw lines in between. 

  //This DID cycle through the bodys of the world, but instead we will cycle through the components and each component just handles its bodies.
  b2Vec2 points[4];
  for (int i = 0; i < 4; i++)
  {
    points[i] = ((b2PolygonShape*)mPhysBody->GetFixtureList()->GetShape())->m_vertices[i];
    RotateAndTranslate(points[i], mPhysBody->GetWorldCenter(), mPhysBody->GetAngle());
  }

  DrawShape(points, 4);

  if (IsDynamic)
  {
    DisplayAngleIndicator();
  }
}

void SDLRectComponent::DisplayAngleIndicator()
{ 
  //Draw the indicator line, which goes from the center to the edge in the direction the object is pointing.
  SDL_SetRenderDrawColor(mnorenderer, 200, 50, 50, 255);

  b2Vec2 center {M2P * mPhysBody->GetWorldCenter()};
  b2Vec2 endpoint {center.x + mWidth/2 * cos(owner->GetAngle()), center.y + mWidth/2 * sin(owner->GetAngle())};

  DrawLine(mPixelX, mPixelY, endpoint.x, endpoint.y);
}

void SDLRectComponent::DrawLine(int x0, int y0, int x1, int y1)
{
  SDL_RenderDrawLine(mnorenderer, x0, y0, x1, y1);
}

void SDLRectComponent::DrawShape(b2Vec2* points, int numSegments)
{
  for (int i = 0; i < numSegments; i++)
  { 
    DrawLine(points[i].x*M2P, points[i].y*M2P,
             points[(i+1) > (numSegments-1) ? 0 : (i+1)].x*M2P, points[(i+1)> (numSegments-1) ? 0 : (i+1)].y * M2P);
  }
}

void SDLRectComponent::RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle)
{
  //Rotate the points and put them back to where they go relative to the world around them and the body.
    b2Vec2 tmp;
    tmp.x = vector.x * cos(angle) - vector.y * sin(angle);
    tmp.y = vector.x * sin(angle) + vector.y * cos(angle);
    vector = tmp+center;
}