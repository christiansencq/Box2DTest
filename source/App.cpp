#include "App.h"
#include "GameMatchState.h"

//SDL_Rect srcR, destR;

App& App::Singleton()
{
    static App theApp;
    return theApp;
}

bool App::Init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL Initialized" << std::endl;

        m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (m_Window)
        {
            std::cout << "Window created!" << std::endl;
        }

        m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
        if(m_Renderer)
        {
            SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
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
    
    m_ScriptLoader = ScriptLoader{};

    std::unique_ptr<GameMatchState> physState = std::make_unique<GameMatchState>(m_Renderer, m_ScriptLoader);
    PushState(std::move(physState));

    return isRunning;
}

void App::Run()
{
    if (m_Window)
    {
        isRunning = true;
        while (isRunning)
        {
            State* topState = App::TopState();

            assert(topState && "There is no scene!");
            if (topState)
            {
                //May want to move event polling to here, rather than within the states?
                // while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
                //Convert to seconds.
                // float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
                // deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
                // ticksLastFrame = SDL_GetTicks(); 
                topState->HandleEvents();
                topState->Update();
                topState->Render(m_Renderer);
            }
        }
    }
}

void App::PushState(std::unique_ptr<State> state)
{
    assert(state && "Dont push nullptr as scene.");

    if (state)
    {
        state->Init();
        m_StateStack.emplace_back(std::move(state));
    }
}

void App::PopToMenu()
{
    while(m_StateStack.size() > 1)
    {
        m_StateStack.pop_back();
    }
}

State* App::TopState()
{
    if (m_StateStack.empty())
    {
        return nullptr;
    }

    return m_StateStack.back().get();
}

App::~App()
{
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    m_Window = nullptr;
    m_Renderer = nullptr;
    TTF_Quit();
    SDL_Quit();
}
