#ifndef PLAYER_OWNER_COMPONENT
#define PLAYER_OWNER_COMPONENT

#include "Component.h"
#include "../Player.h"
// class Player;

class PlayerOwnerComponent : public Component
{
public:

    PlayerOwnerComponent(Player* player);
    virtual ~PlayerOwnerComponent() override {}
    virtual void Initialize() override {}
    virtual void HandleEvents(SDL_Event &event) override {}
    virtual void HandleKeyPress(SDL_Keycode key) override {}
    virtual void HandleKeyRelease(SDL_Keycode key) override {}
    virtual void Update() override {}
    virtual void Render() override {}

    Player* GetPlayer() {return mPlayer;}

    Entity* GetOwner() {return owner;}
    Entity* owner;

private:

    Player* mPlayer;

};


#endif
