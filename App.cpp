#include "App.h"

SDL_Rect srcR, destR;

App& App::Singleton()
{
    static App theApp;
    return theApp;
}

bool App::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL Initialized" << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created!" << std::endl;
        }

        isRunning = true;
    }
    else
    {
        std::cout << "Initialization error! %s" << SDL_GetError() << std::endl;
        isRunning = false;
    }

    if (TTF_Init() < 0)
    {
        std::cout << "TTF Load error! %s" << TTF_GetError() << std::endl; 
        isRunning = false;
    }
    
    std::unique_ptr<GameMatchState> physState = std::make_unique<GameMatchState>(renderer);
    PushState(std::move(physState));

    return isRunning;
}

void App::Run()
{
    if (window)
    {
        isRunning = true;
        while (isRunning)
        {
            State* topState = App::TopState();

            assert(topState && "There is no scene!");
            if (topState)
            {
                /*
                while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
                //Convert to seconds.
                float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
                deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
                ticksLastFrame = SDL_GetTicks(); 
                */
                topState->HandleEvents();
                topState->Update();
                topState->Render(renderer);
            }
        }
    }
}

void App::PushState(std::unique_ptr<State> state)
{
    assert(state && "Dont push nullptr as scene.");

    if (state)
    {
        state->init();
        mStateStack.emplace_back(std::move(state));
    }
}

void App::PopToMenu()
{
    while(mStateStack.size() > 1)
    {
        mStateStack.pop_back();
    }

    if (TopState())
    {

    }
}

State* App::TopState()
{
    if (mStateStack.empty())
    {
        return nullptr;
    }

    return mStateStack.back().get();
}

App::~App()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;
    TTF_Quit();
    SDL_Quit();
}