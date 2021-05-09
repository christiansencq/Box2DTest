#ifndef APP_H
#define APP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "PhysicsState.h"
#include "State.h"
//#include "Constants.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <memory>

//class State;


class App 
{
public:
    ~App();
    static App& Singleton();

    bool init(const char* title, int widthPhysics, int height, bool fullscreen);

    void PushState(std::unique_ptr<State> state);
    void PopState();
    void PopToMenu();
    State* TopState();

    void Run();

    inline void QuitApp() { isRunning = false; };
    inline bool running() { return isRunning; };
    //SDL_Renderer* GetRenderer() { return renderer; }

private:
    bool isRunning = false;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Window* window;
    std::vector<std::unique_ptr<State>> mStateStack;
};

#endif