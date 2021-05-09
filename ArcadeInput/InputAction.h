#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include <functional>
#include <stdint.h>

typedef uint8_t InputKey;
typedef uint8_t InputState;
//typedef uint8_t MouseButton;

typedef std::function<void(int dt, InputState)> InputAction;

struct ButtonAction
{
    int key;
    int action;
};

// struct MousePosition
// {
//     int32_t xPos, yPos;
// };

// typedef std::function<void(const MousePosition& mousePosition)> MouseMovedAction;
// typedef std::function<void(InputState state, const MousePosition& position)> MouseInputAction;

// struct MouseButtonAction
// {
//     MouseButton mouseButton;
//     MouseInputAction mouseInputAction;
// }

#endif