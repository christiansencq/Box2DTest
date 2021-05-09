#include "InputController.h"
#include "GameController.h"
#include <SDL2/SDL.h>
#include <iostream>
//Handling input events here.

InputController::InputController() : mQuit(nullptr), mCurrentController(nullptr)
{

}

void InputController::Init(InputAction quitAction)
{
	mQuit = quitAction;
}

void InputController::Update(uint32_t dt)
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
			{
				mQuit(dt, SDL_PRESSED);
			}
			case SDL_KEYDOWN:
			{
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					std::cout << "ESCAPE EVENT!" << std::endl;
					mQuit(dt, SDL_PRESSED);
					
				}
			}
			case SDL_KEYUP:
				if (mnoptrCurrentController)
				{
					InputAction action = mnoptrCurrentController->GetActionForKey(sdlEvent.key.keysym.sym);

					action(dt, static_cast<InputState>(sdlEvent.key.state));
				}
				break;
		}
	}
}

void InputController::SetGameController(GameController* controller)
{
	mnoptrCurrentController = controller;
}