#include "AssetManager.h"

AssetManager::AssetManager()
{

}


AssetManager::~AssetManager()
{
    
}

void AssetManager::ClearData() 
{ 
    //Need to call TTF_CloseFont for all in fonts?
    m_Fonts.clear(); 
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
