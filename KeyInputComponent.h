#ifndef KEY_INPUT_COMPONENT_H
#define KEY_INPUT_COMPONENT_H

#include <map>
#include <array>
#include <vector>

#include "PhysicsComponent.h"
#include "Component.h"
#include "Commands.h"
#include "Constants.h"


class KeyInputComponent : public Component
{
public:

    KeyInputComponent(std::array<SDL_Keycode, 4> action_keys);
    virtual ~KeyInputComponent();


    void Initialize() override;
    void HandleEvents(SDL_Event &event) override;
    void HandleKeyPress(SDL_Keycode key) override;
    void HandleKeyRelease(SDL_Keycode key) override;
    void Update() override {}
    void Render(SDL_Renderer* renderer) override {}
    void printType() const override {}

    //Currently, Commands are Added in this's initializer.  Later, will be added externally, from the state/pre-game.
    template <typename T, typename... TArgs>    
    T& AddCommand(TArgs&&... args)
    {
        T* newCommand(new T(std::forward<TArgs>(args)...)); //Would pass 'this' into the constructor, then wouldn't need the next lines.
        newCommand->owningComponent = this;
        commands.push_back(newCommand);
        commandTypeMap[&typeid(*newCommand)] = newCommand;
        //ActionMap

        newCommand->Initialize();
        return *newCommand;
    } 
    
    template<typename T>
    T* GetCommand()
    {
        return static_cast<T*>(commandTypeMap[&typeid(T)]);
    }

    Entity* owner;
    PhysicsComponent* physicsComp;

    std::array<SDL_Keycode, 4> actionKeys;
    //std::array<SDL_Keycode, 4> actionKeys;
    
    //const std::array<const SDL_Keycode, 4> c_actionKeys;

    std::vector<Command*> commands;
    std::map<const std::type_info*, Command*> commandTypeMap;

    std::map<Actions, Command*> ActionMap;
//case SDLK_UP:
        
private:


};

#endif