#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

// #include "../Data/Constants.h"
#include "Component.h"
#include "../Player.h"
#include "../AssetManager.h"

class Entity;

class TextComponent : public Component
{
public:
    TextComponent(AssetManager& asset_manager, SDL_Renderer* renderer, std::string text, std::string font_name, SDL_Color color);
    ~TextComponent();

    virtual void Initialize() override;
    virtual void HandleEvents(SDL_Event &event) override {}
    virtual void Render() override;
    virtual void Update() override;

    void SetText(std::string text);

    Entity* owner;

private:
    // std::shared_ptr<Player> m_Player;
    AssetManager& m_AssetManager;
    SDL_Renderer* m_Renderer;

    std::string m_FontName;
    TTF_Font* m_Font;

    SDL_Rect m_TextRect;
    std::string m_Text;
    SDL_Texture* m_Texture;

    SDL_Color m_Color;

};


#endif
