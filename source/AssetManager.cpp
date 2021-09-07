#include "AssetManager.h"

AssetManager::AssetManager(SDL_Renderer* renderer)
 : m_Renderer(renderer)
{

}

// AssetManager::AssetManager()
// {
//
// }

AssetManager::~AssetManager()
{
    
}

void AssetManager::ClearData() 
{ 
    //Need to call TTF_CloseFont for all in fonts?
    m_Fonts.clear(); 
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	m_Textures.emplace(id, LoadTexture(path));
}

SDL_Texture* AssetManager::LoadTexture(const char* texture_path)
{
    SDL_Surface* tempSurface = IMG_Load(texture_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return texture;
}


SDL_Texture* AssetManager::GetTexture(std::string texture_id)
{
    return m_Textures[texture_id];
}

void AssetManager::AddFont(std::string font_id, const char* file_path, int font_size)
{
	m_Fonts.emplace(font_id, LoadFont(file_path, font_size));
}

TTF_Font* AssetManager::LoadFont(const char* file_name, int font_size)
{
    return TTF_OpenFont(file_name, font_size);
}

TTF_Font* AssetManager::GetFont(std::string font_id)
{
    return m_Fonts[font_id];
}
