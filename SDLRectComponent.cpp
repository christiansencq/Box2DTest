#include "SDLRectComponent.h"

//SDLRectComponent::SDLRectComponent() : SDLRectComponent(0, 0, 1, 1) {}

// SDLRectComponent::SDLRectComponent(SDL_Renderer* renderer, int PixelW, int PixelH) 
//  : mnorenderer(renderer), mWidth(PixelW), mHeight(PixelH), mColor(BLACK)
// {


// }

SDLRectComponent::SDLRectComponent(SDL_Renderer* renderer, int PixelW, int PixelH, SDL_Color color) 
 : mnorenderer(renderer), mWidth(PixelW), mHeight(PixelH), mColor(color)
{

}

void SDLRectComponent::Initialize()
{
  mWidth = owner->GetPixelSize().x;
  mHeight = owner->GetPixelSize().y;
  
  physicsComp = owner->GetComponent<PhysicsComponent>();

  //Also set up the renderer, surface pointers here?
  // renderer = owner->GetRenderer();
}

void SDLRectComponent::Update() 
{


}

void SDLRectComponent::Render(SDL_Renderer* renderer) 
{
  // Draw a rect here.
   
  DisplayRect(physicsComp->GetPhysBody()->GetWorld());
  

}

void SDLRectComponent::DisplayRect(b2World* world)
{
  //Breaks down the PhysicsBody into a set of vertices that we can draw lines in between.
 
  SDL_SetRenderDrawColor(mnorenderer, mColor.r, mColor.g, mColor.b, mColor.a);
   //This DID cycle through the bodys of the world, but instead we will cycle through the components and each component just handles its bodies.
  b2Body* tmpbody = physicsComp->GetPhysBody();
  b2Vec2 points[4];
  
  for (int i = 0; i < 4; i++)
  {
    points[i] = ((b2PolygonShape*)tmpbody->GetFixtureList()->GetShape())->m_vertices[i];
    RotateAndTranslate(points[i], tmpbody->GetWorldCenter(), tmpbody->GetAngle());
  }
  DrawRect(points, tmpbody->GetWorldCenter(), tmpbody->GetAngle());

  if (physicsComp->IsDynamic())
  {
    DisplayAngleIndicator(world, physicsComp->GetPhysBody());
  }


  /*
  radius OR:
  height/2
  */

}

void SDLRectComponent::DisplayAngleIndicator(b2World* world, b2Body* tmpbody)
{
  //Draw the indicator line, which goes from the center to the edge in the direction the object is pointing.
  SDL_SetRenderDrawColor(mnorenderer, 200, 50, 50, 255);
  b2Vec2 center = tmpbody->GetLocalCenter()+tmpbody->GetWorldCenter();
  b2Vec2 line[2];
  // line[0] = {tmpbody->GetLocalCenter().x + (sin(tmpbody->GetAngle()) * mHeight), tmpbody->GetLocalCenter().y + (cos(tmpbody->GetAngle()) * mHeight)};
  // line[1] = {tmpbody->GetLocalCenter().x + (cos(tmpbody->GetAngle()) * mWidth/2), tmpbody->GetLocalCenter().y + (sin((tmpbody->GetAngle()) * mWidth/2))};

  line[0] = {tmpbody->GetWorldCenter()};
  line[1] = {tmpbody->GetWorldCenter().x + cos(tmpbody->GetAngle() * mWidth), tmpbody->GetWorldCenter().y + sin(tmpbody->GetAngle() * mWidth)};


  for (int i = 0; i < 2; i++)
    RotateAndTranslate(line[i], tmpbody->GetWorldCenter(), tmpbody->GetAngle());

  DrawLine(line[0].x, line[0].y, line[1].x, line[1].y);
}

void SDLRectComponent::DrawLine(int x0, int y0, int x1, int y1)
{
  SDL_RenderDrawLine(mnorenderer, x0, y0, x1, y1);
}

void SDLRectComponent::DrawRect(b2Vec2* points, b2Vec2 center, float angle)
{
  for (int i = 0; i < 4; i++)
  {
    DrawLine(points[i].x*M2P, points[i].y*M2P,
             points[(i+1) > 3 ? 0 : (i+1)].x*M2P, points[(i+1)>3 ? 0 : (i+1)].y * M2P);
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