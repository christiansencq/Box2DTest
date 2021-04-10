#include "SDLRectComponent.h"

SDLRectComponent::SDLRectComponent() : SDLRectComponent(0, 0, 1, 1) {}

SDLRectComponent::SDLRectComponent(int x, int y, int w, int h) 
{
  mRect = new SDL_Rect{x, y, w, h};
}

SDLRectComponent::SDLRectComponent(float x, float y, float w, float h) 
{
  int iX = static_cast<int>(x);
  int iY = static_cast<int>(y);
  int iW = static_cast<int>(w);
  int iH = static_cast<int>(h);

  mRect = new SDL_Rect{iX, iY, iW, iH};
}

void SDLRectComponent::Update() {
  // Update position.
  mRect->x = owner->GetPixelX();
  mRect->y = owner->GetPixelY();
}

void SDLRectComponent::Render(SDL_Renderer *renderer) {
  // Draw a rect here.
  SDL_SetRenderDrawColor(renderer, 0xBB, 0xFF, 0x33, 0xFF);
  SDL_RenderFillRect(renderer, mRect);

}