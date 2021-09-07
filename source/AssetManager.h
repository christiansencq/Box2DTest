#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

class AssetManager
{
/*
This is for holding and accessing loaded assets, including sprites and font.
*/
public:
    AssetManager(SDL_Renderer* renderer);
    ~AssetManager();
    void ClearData();

    void AddTexture(std::string texture_id, const char* file_path);
    SDL_Texture* LoadTexture(const char* texture_path);
    SDL_Texture* GetTexture(std::string id);

    void AddFont(std::string font_id, const char* file_path, int font_size);
    TTF_Font* LoadFont(const char* file_name, int font_size);
    TTF_Font* GetFont(std::string font_id);

private:
	std::map<std::string, TTF_Font*> m_Fonts;
    std::map<std::string, SDL_Texture*> m_Textures;

    SDL_Renderer* m_Renderer;
};

#endif
