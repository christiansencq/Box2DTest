#pragma once

#include "Component.h"


class KeyInputComponent : Component
{
public:
    virtual void Initialize() override {}
    virtual void HandleEvents(SDL_Event &event) override;
    virtual void HandleKeyPress(SDL_Keycode key) override;
    virtual void Update() override {}
    virtual void Render(SDL_Renderer* renderer) override {}
    virtual void printType() const override {}

private:

};