#ifndef SELECTABLE_COMPONENT_H
#define SELECTABLE_COMPONENT_H

#include "../Constants.h"
#include "Component.h"

class Entity;

class SelectableComponent : public Component
{
public:
    explicit SelectableComponent(SDL_Renderer* renderer);
    ~SelectableComponent();

    virtual void Initialize() override;
    virtual void Render() override;
    virtual void Update() override;
    
    void DrawCircle();
    void Select() { isSelected = true; }
    void Deselect() { isSelected = false; }

    Entity* owner;

private:
    SDL_Renderer* m_Renderer;
    bool isSelected;
    SDL_Color m_Color;
    int m_Diameter;
    float m_PixelX, m_PixelY;
    static constexpr float addRad = 10.0f;
};


#endif
