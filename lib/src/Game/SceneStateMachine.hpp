/**
 *  @file     lib/src/Game/SceneStateMachine.hpp
 *  @author   tabis on the 2020-01-22
 *  @date     2020-01-22
 * 
 *  project: APCPPLib
 * 
 */

#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <stack>

#include "IScene.hpp"

/// @namespace Game.
/// @brief game namespace.
namespace Game
{

    /// @enum scene_behavior
    /// @brief States sent to the mediator via the notifie method
    enum scene_state
    {
        POP,
        SWAP
    };

    class IMediator
    {
    public:

        /** 
         * @brief notify the mediator that a scenes changed it's state
         * @param state : state of the scene
         * @param new_scene : potential new scene to push in case of a swap
         */
        virtual void notify(scene_state state, IScene *new_scene) = 0;
    };

    class SceneStateMachine : public IMediator
    {
    public:

        // Ctor / Dtor
        /** 
         * @brief SceneStateMachine
         * Constructor That initialize callbacks
         */
        SceneStateMachine();

        /** 
         * @brief SceneStateMachine
         * Destructor that deletes the content of the scene stack.
         */
        ~SceneStateMachine();

        // Interface
        /** 
         * @brief notify the mediator that a scenes changed it's state
         * @param state : state of the scene
         * @param new_scene : potential new scene to push in case of a swap
         */
        void notify(scene_state state, IScene *new_scene) override;

        // Running
        /** 
         * @brief Updates the scene on top of the stack
         * @return true if the action was successful, false otherwise
         */
        bool update();

        // Memory modification        
        /** 
         * @brief Push a scene onto the stack 
         * @param scene : the scene to push
         */
        void push(std::shared_ptr<Game::IScene> &scene);
        
        /** 
         * @brief Swap the scene on top of the stack with the scene passed as parameter.
         * @param scene : the scene that will be on top of the stack.
         */
        void swap(std::shared_ptr<Game::IScene> &scene);

        /** 
         * @brief Pop scenes until the scene name has been reached.
         * @param name : the name of the scene to stop to.
         */
        void pop(const std::string &name);

        /** 
         * @brief Pop the scene on top of the stack.
         */
        void pop();        
                
        /** 
         * @brief Clear all scenes from the stack.
         */
        void clear();
        
        /** 
         * @brief Use the remove methods of the scene on top of the stack.
         */
        void remove();

        // Getters
        /** 
         * @brief Get the size of the stack.
         * @return the size of the stack.
         */
        std::size_t size() const;

        /** 
         * @brief Get the name of the scene on top of the stack.
         * @return the name of the scene on top of the stack.
         */
        std::string name() const;

        /** 
         * @brief Check if the stack is empty.
         * @return true if the stack is empty, false otherwise.
         */
        bool empty() const;
        
    private:

        /** 
         * @brief When the mediator is notified via the POP state, pops the scene on top of the stack.
         * @param scene : Unused parameter.
         */
        void popCallback(IScene *scene);

        /** 
         * @brief When the mediator is notified via the SWAP state, swaps the scene on top of the stack.
         * @param scene : the scene to swap.
         */
        void swapCallback(IScene *scene);

        /*! the stack of scenes */
        std::stack<std::shared_ptr<Game::IScene>> _scenes;

        /*! using callbacks via the states of the scenes */
        std::unordered_map<scene_state, std::function<void(SceneStateMachine &, IScene *)>> _callbacks;
   };
}