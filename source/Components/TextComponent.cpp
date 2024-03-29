#include "TextComponent.h"
#include "../Entity.h"

TextComponent::TextComponent(AssetManager& asset_manager, SDL_Renderer* renderer, std::string text, std::string font_name, SDL_Color color) 
 : m_AssetManager(asset_manager), m_Renderer(renderer), m_FontName(font_name), m_Text(text), m_Color(color)
{

}

TextComponent::~TextComponent()
{

}

void TextComponent::Initialize()
{
    m_TextRect.w = owner->GetPixelSize().x;
    m_TextRect.h = owner->GetPixelSize().y;
    m_TextRect.x = owner->GetPixelPos().x;
    m_TextRect.y = owner->GetPixelPos().y;
    m_Font = m_AssetManager.GetFont(m_FontName);
    SetText(m_Text);
}

void TextComponent::Render()
{
    // std::cout << "Renderer resolution set ? " << SDL_RenderSetLogicalSize(m_Renderer, 640, 480) << "\n";
    //m_Texture contains the actual text, which is changed by SetText.
    SDL_RenderCopy(m_Renderer, m_Texture, NULL, &m_TextRect);
}

void TextComponent::Update()
{
    m_TextRect.x = owner->GetPixelPos().x;
    m_TextRect.y = owner->GetPixelPos().y;
    
}


void TextComponent::SetText(std::string text) 
{
    std::cout << "Setting Text.\n";
   //Update the text to reflect the new player score.
    const char* txt = text.c_str();
    SDL_Surface* surface = TTF_RenderText_Blended(m_Font, txt, m_Color);

    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);
    m_TextRect.w = surface->w;
    m_TextRect.h = surface->h;
    SDL_QueryTexture(m_Texture, NULL, NULL, &m_TextRect.x, &m_TextRect.y);
}
