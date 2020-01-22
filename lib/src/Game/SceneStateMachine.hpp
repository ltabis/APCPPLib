//
// Created by tabis on 21/01/2020.
//

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
    enum scene_state
    {
        POP,
        SWAP
    };

    class IMediator
    {
    public:

        virtual void notify(const std::string &sender, scene_state state, IScene *new_scene) = 0;
    };

    class SceneStateMachine : public IMediator
    {
    public:

        // Ctor / Dtor
        SceneStateMachine();

        ~SceneStateMachine();

        // Interface
        void notify(const std::string &sender, scene_state state, IScene *new_scene) override;

        // Running
        bool update();

        // Memory modification        
        void push(std::shared_ptr<Game::IScene> &scene);
        
        void swap(std::shared_ptr<Game::IScene> &scene);

        void pop(const std::string &name);

        void pop();        
                
        void clear();
        
        void remove();

        // Getters
        std::size_t size() const;

        std::string name() const;

        bool empty() const;
        
    private:

        void popCallback(IScene *scene);

        void swapCallback(IScene *scene);

        /*! the stack of scenes */
        std::stack<std::shared_ptr<Game::IScene>> _scenes;

        std::unordered_map<scene_state, std::function<void(SceneStateMachine &, IScene *)>> _callbacks;
   };
}