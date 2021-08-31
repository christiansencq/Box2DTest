#ifndef SELECTABLE_COMPONENT_H
#define SELECTABLE_COMPONENT_H

#include "Constants.h"
#include "Component.h"
#include "../Player.h"

class Entity;
//Make this inherit from SDLCircleComponent instead?

class SelectableComponent : public Component
{
public:
    // SelectableComponent(SDL_Renderer* renderer, std::shared_ptr<Player> player);
    SelectableComponent(SDL_Renderer* renderer);
    SelectableComponent(SDL_Renderer* renderer, std::vector<int> color);
    SelectableComponent(SDL_Renderer* renderer, SDL_Color color);
    ~SelectableComponent();

    virtual void Initialize() override;
    virtual void Render() override;
    virtual void Update() override;

    // void SetColor(std::vector<int> color);
    
    void Select() { isSelected = true; }
    void Deselect() { isSelected = false; }

    Entity* owner;

private:
    void DrawCircle();


    SDL_Renderer* m_Renderer;
    bool isSelected;
    SDL_Color m_Color;
    int m_Diameter;
    float m_PixelX, m_PixelY;
    static constexpr float addRad = 10.0f;
};


#endif
