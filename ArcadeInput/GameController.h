#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "InputAction.h"
#include <vector>

/*
    Make InputKey an enum.
*/

class GameController
{
public:
    GameController();
    InputAction GetActionForKey(InputKey key);

    void AddInputActionForKey(const ButtonAction& buttonAction);
    void ClearAll();

    static bool IsPressed(InputState state);
    static bool IsReleased(InputState state);
    static InputKey ActionKey();
    static InputKey CancelKey();

private:
    std::vector<ButtonAction> mButtonActions;
};
