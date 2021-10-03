#include "SpriteComponent.h"
#include "../Entity.h"
#include <cmath>

SpriteComponent::SpriteComponent(AssetManager& asset_manager, SDL_Renderer* renderer, std::string id, b2Vec2 sprite_size)
 : m_AssetManager(asset_manager), m_Renderer(renderer), m_SpriteName(id), m_SpriteSize(sprite_size)
{

}

void SpriteComponent::Initialize()
{
    destRect.w = owner->GetPixelSize().x;
    destRect.h = owner->GetPixelSize().y;
    // destRect.x = owner->GetPixelPos().x;
    // destRect.y = owner->GetPixelPos().y;
    destRect.x = (owner->GetPixelPos().x - owner->GetPixelSize().x/2);
    destRect.y = (owner->GetPixelPos().y - owner->GetPixelSize().y/2);
    m_Texture = m_AssetManager.GetTexture(m_SpriteName);

    srcRect.x = srcRect.y = 0;
    srcRect.w = owner->GetPixelSize().x;
    srcRect.h = owner->GetPixelSize().y;
    m_Angle = 180/M_PI * owner->GetAngle();

}

void SpriteComponent::Render()
{
    // SDL_RenderCopyEx(m_Renderer, m_Texture, &srcRect, &destRect, m_Angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);

    SDL_RenderCopyEx(m_Renderer, m_Texture, &srcRect, &destRect, m_Angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

void SpriteComponent::Update()
{
    destRect.x = (owner->GetPixelPos().x - owner->GetPixelSize().x/2);
    destRect.y = (owner->GetPixelPos().y - owner->GetPixelSize().y/2);
    // m_Angle = M_PI * owner->GetAngle();
    m_Angle = 180/M_PI * owner->GetAngle();
}



