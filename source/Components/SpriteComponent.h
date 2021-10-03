#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Component.h"

#include "../AssetManager.h"


class SpriteComponent : public Component
{
public:

    SpriteComponent(AssetManager& asset_manager, SDL_Renderer* renderer, std::string id, b2Vec2 sprite_size);

    virtual void Initialize() override;
    virtual void HandleEvents(SDL_Event &event) override {}
    virtual void Render() override;
    virtual void Update() override;

    void SetTexture(std::string id);

    Entity* owner;

private:

    AssetManager& m_AssetManager;
    SDL_Renderer* m_Renderer;

    std::string m_SpriteName;

    SDL_Texture* m_Texture;

    SDL_Rect srcRect, destRect;
    b2Vec2 m_SpriteSize;
    float m_Angle;

};


#endif
