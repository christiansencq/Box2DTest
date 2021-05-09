#include "SDL2/SDL.h"
#include "Entity.h"

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(Entity& entity) = 0;
};


class ForwardCommand : public Command
{
    virtual void execute(Entity& entity) 
    { 
        //Go into the Entity's InputActionsComponent, which would store the actions for
        //The Forward Command.
        entity.GetComponent<KeyInputComponent>()->FWDCommand(); 
    }
};


class InputHandler
{
public:
    InputHandler() {}

    Command* HandleInput() 
    {
        //
    }

private:

};