#include "SDLRectComponent.h"
#include "../Entity.h"
//Problematic coupling here: 
#include "PhysicsComponent.h"

SDLRectComponent::SDLRectComponent(SDL_Renderer* renderer, SDL_Color color) 
 : m_Renderer(renderer), m_Color(color)
{

}

void SDLRectComponent::Initialize()
{
  m_Width = owner->GetPixelSize().x;
  m_Height = owner->GetPixelSize().y;
  m_PixelX = owner->GetPixelPos().x;
  m_PixelY = owner->GetPixelPos().y;

  //Do not want to know about PhysicsBody.  Need to refactor so that these do not have to know about each other.
  m_PhysBody = owner->GetComponent<PhysicsComponent>()->GetPhysBody();

}

void SDLRectComponent::Update() 
{

  //Check if not static?
  if (IsDynamic)
  {
    m_PixelX = owner->GetPixelPos().x;
    m_PixelY = owner->GetPixelPos().y;
  }

}

void SDLRectComponent::Render() 
{
  //Set colors in here before .
  SDL_SetRenderDrawColor(m_Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
  // Draw a rect here.   
  DisplayRect();
}

void SDLRectComponent::DisplayRect()
{
  //Move this vector calculation into Entity?
  //Breaks down the PhysicsBody into a set of vertices that we can draw lines in between. 
  b2Vec2 points[4];
  for (int i = 0; i < 4; i++)
  {
    points[i] = ((b2PolygonShape*)m_PhysBody->GetFixtureList()->GetShape())->m_vertices[i];
    RotateAndTranslate(points[i], m_PhysBody->GetWorldCenter(), m_PhysBody->GetAngle());
  }

  DrawShape(points, 4);

//  if (IsDynamic)
//  {
//    DisplayAngleIndicator();
//  }
}

void SDLRectComponent::DisplayAngleIndicator()
{ 
  //Draw the indicator line, which goes from the center to the edge in the direction the object is pointing.
  SDL_SetRenderDrawColor(m_Renderer, 200, 50, 50, 255);

  b2Vec2 center {M2P * m_PhysBody->GetWorldCenter()};
  b2Vec2 endpoint {center.x + m_Width/2 * cos(owner->GetAngle()), center.y + m_Width/2 * sin(owner->GetAngle())};

  DrawLine(m_PixelX, m_PixelY, endpoint.x, endpoint.y);
}

void SDLRectComponent::DrawLine(int x0, int y0, int x1, int y1)
{
  SDL_RenderDrawLine(m_Renderer, x0, y0, x1, y1);
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
