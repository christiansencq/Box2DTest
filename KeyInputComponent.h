#ifndef KEY_INPUT_COMPONENT_H
#define KEY_INPUT_COMPONENT_H

#include "PhysicsComponent.h"


class KeyInputComponent : public Component
{
public:
    void Initialize() override;
    void HandleEvents(SDL_Event &event) override;
    void HandleKeyPress(SDL_Keycode key) override;
    void HandleKeyRelease(SDL_Keycode key) override;
    void Update() override {}
    void Render(SDL_Renderer* renderer) override {}
    void printType() const override {}

    Entity* owner;

private:
    PhysicsComponent* physicsBody;

};

#endif