#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include "InputAction.h"

class GameController;

//May be more of an 'InputManager'

class InputController
{
public:
    InputController();
    void Init(InputAction quitAction);
    void Update(uint32_t dt);
    void SetGameController(GameController* controller);

private:
    InputAction mQuit;
    GameController* mCurrentController;
};

#endif