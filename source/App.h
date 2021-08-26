#ifndef APP_H
#define APP_H

#include <cassert>
#include <iostream>
#include <vector>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "ScriptLoader.h"
#include "State.h"

class App 
{
public:
    ~App();
    static App& Singleton();

    bool Init(const char* title, int width, int height, bool fullscreen);

    void PushState(std::unique_ptr<State> state);
    void PopState();
    void PopToMenu();
    State* TopState();

    void Run();

    inline void QuitApp() { isRunning = false; };
    inline bool running() { return isRunning; };

private:
    bool isRunning = false;
    
    SDL_Renderer* m_Renderer;
    SDL_Surface* m_Surface;
    SDL_Window* m_Window;
    
    std::shared_ptr<ScriptLoader> m_ScriptLoader;
    std::vector<std::unique_ptr<State>> m_StateStack;
};

#endif
