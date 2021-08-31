#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "App.h"
#include "State.h"
#include "EntityManager.h"
#include "ObjectFactory.h"



class PauseState : public State
{
public:

    PauseState(SDL_Renderer* renderer, std::shared_ptr<ObjectFactory> object_factory);
    ~PauseState();

    virtual void HandleEvents() override;
    virtual void Update() override;
    virtual void Render(SDL_Renderer* renderer) override;


private:

    SDL_Renderer* m_Renderer;
    std::unique_ptr<EntityManager> m_PauseEntityManager;

};

#endif
