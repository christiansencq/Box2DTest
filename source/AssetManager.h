#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>

#include "SDL2/SDL_ttf.h"

class AssetManager
{
/*
This is for holding and accessing loaded assets.
*/
public:
    AssetManager();
    ~AssetManager();
    void ClearData();

    void AddFont(std::string font_id, const char* file_path, int font_size);
    TTF_Font* LoadFont(const char* file_name, int font_size);
    TTF_Font* GetFont(std::string font_id);

private:
	std::map<std::string, TTF_Font*> m_Fonts;


};

#endif
