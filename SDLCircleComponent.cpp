#include "SDLCircleComponent.h"

SDLCircleComponent::SDLCircleComponent(SDL_Renderer* renderer, SDL_Color color)
    : mnorenderer(renderer), mColor(color)
{
}

void SDLCircleComponent::Initialize() 
{
  //mPhysBody = owner->GetComponent<PhysicsComponent>()->GetPhysBody();
  
  //Now Can base these off the PhysicsComponents?
  mDiameter = owner->GetPixelSize().x;
  mPixelX = owner->GetPixelPos().x;
  mPixelY = owner->GetPixelPos().y;

}

void SDLCircleComponent::Update()
{
  mPixelX = owner->GetPixelPos().x;
  mPixelY = owner->GetPixelPos().y;
  //mAngle = owner->GetAngle();
}

void SDLCircleComponent::Render(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(mnorenderer, mColor.r, mColor.g, mColor.b, mColor.a);
  DrawCircle();
}


void SDLCircleComponent::DrawCircle()
{

   int32_t x = (mDiameter/2 - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - mDiameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      //Uses midpoint algorithm to draw
      SDL_RenderDrawPoint(mnorenderer, mPixelX + x, mPixelY - y);
      SDL_RenderDrawPoint(mnorenderer, mPixelX + x, mPixelY + y);
      SDL_RenderDrawPoint(mnorenderer, mPixelX - x, mPixelY - y);
      SDL_RenderDrawPoint(mnorenderer, mPixelX - x, mPixelY + y);
      SDL_RenderDrawPoint(mnorenderer, mPixelX + y, mPixelY - x);
      SDL_RenderDrawPoint(mnorenderer, mPixelX + y, mPixelY + x);
      SDL_RenderDrawPoint(mnorenderer, mPixelX - y, mPixelY - x);
      SDL_RenderDrawPoint(mnorenderer, mPixelX - y, mPixelY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }
      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - mDiameter);
      }
   }
   DisplayAngleIndicator();
}

void SDLCircleComponent::DisplayAngleIndicator()
{ 
  //Draw the indicator line, which goes from the center to the edge in the direction the object is pointing.
  SDL_SetRenderDrawColor(mnorenderer, 200, 50, 50, 255);

  b2Vec2 center {mPixelX, mPixelY};
  //Using cos/sin is costly, look up possibility of using a lookup table for these values instead.
  //Also, this is the only PhysBody reference in here. Possible to have Entity keep track of its angle?
  b2Vec2 endpoint {center.x + mDiameter/2 * cos(owner->GetAngle()), 
                   center.y + mDiameter/2 * sin(owner->GetAngle())};
  DrawLine(center.x, center.y, endpoint.x, endpoint.y);
}

void SDLCircleComponent::DrawLine(int x0, int y0, int x1, int y1)
{
  SDL_RenderDrawLine(mnorenderer, x0, y0, x1, y1);
}

void SDLCircleComponent::RotateAndTranslate(b2Vec2& vector, const b2Vec2& center, float angle)
{
  //Rotate the points around the 'center'
    b2Vec2 tmp;
    tmp.x = vector.x * cos(angle) - vector.y * sin(angle);
    tmp.y = vector.x * sin(angle) + vector.y * cos(angle);
    vector = tmp + center;
}