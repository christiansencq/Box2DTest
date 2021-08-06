#ifndef KEY_INPUT_COMPONENT_H
#define KEY_INPUT_COMPONENT_H

#include <map>
#include <array>
#include <vector>

//#include "PhysicsComponent.h"
#include "Component.h"
#include "../Commands/Commands.h"
#include "../Constants.h"


class KeyInputComponent : public Component
{
public:

    KeyInputComponent(std::array<SDL_Keycode, 4> action_keys);
    virtual ~KeyInputComponent();

    virtual void Initialize() override;
    virtual void HandleEvents(SDL_Event &event) override;
    virtual void HandleKeyPress(SDL_Keycode key) override;
    virtual void HandleKeyRelease(SDL_Keycode key) override;
    virtual void Update() override {}

    template <typename T, typename... TArgs>    
    T& AddCommand(TArgs&&... args)
    {
        T* newCommand(new T(std::forward<TArgs>(args)...)); 
        newCommand->owningComponent = this; //Could use move?
        m_Commands.push_back(newCommand);
        m_CommandTypeMap[&typeid(*newCommand)] = newCommand;

        newCommand->Initialize();
        return *newCommand;
    } 
    
    template <typename T, typename... TArgs>    
    T& AddCommand2(TArgs&&... args)
    {
        T* newCommand(std::make_unique<T>(std::forward<TArgs>(args)...)); 
        newCommand->owningComponent = this; //Could use move?
        m_Commands.push_back(newCommand);
        m_CommandTypeMap[&typeid(*newCommand)] = newCommand;

        newCommand->Initialize();
        return *newCommand;
    } 
    
    template<typename T>
    T* GetCommand()
    {
        return static_cast<T*>(m_CommandTypeMap[&typeid(T)]);
    }

    //Move this directly to the Component.h?
    Entity* GetOwner() { return owner; }
    Entity* owner;

    void AssignAction(Actions actionName, Command* actionVerb) {
        m_ActionMap[actionName] = actionVerb;
    }
       
private:
    std::array<SDL_Keycode, 4> m_ActionKeys;
    std::vector<Command*> m_Commands;
    std::map<const std::type_info*, Command*> m_CommandTypeMap;
    std::map<Actions, Command*> m_ActionMap;
};

#endif
