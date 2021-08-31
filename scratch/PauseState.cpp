#include "PauseState.h"

PauseState::PauseState()
{
    /* 
     * Create Menu Entities: 
     * MenuSelector (SDLRect that is controllable by keys)
     * Buttons (Text Objects that will either A) Exit Game, or B)Return to Game State. 
     */

    

}

PauseState::~PauseState()
{

}

void PauseState::HandleEvents()
{
    //Enter - Select Option
    //Up, Down - Change Selection
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            App::Singleton().QuitApp();
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    App::Singleton().QuitApp();
                // case SDLK_UP:

                // case SDLK_DOWN:
                    
                default:
                    break;

            }
            break;
        }
    }
}


void PauseState::Update()
{

}

void PauseState::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x44, 0x11, 0x88, 0xFF);
    SDL_RenderClear(renderer);

    
    SDL_RenderPresent(renderer);
}

