//
// Created by tabis on 21/01/2020.
//

#pragma once

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
        POP = 1,
        SWAP = 2,
        INCATIVE = 4
    };

    class IMediator
    {
    public:

        virtual void notify(const std::string &sender, std::size_t state) = 0;
    };

    class SceneStateMachine : public IMediator
    {
    public:

        void notify(const std::string &sender, std::size_t state) override;

        // Running
        bool update();

        // Memory modification        
        void push(std::shared_ptr<Game::IScene> &scene);
        
        void swap(std::shared_ptr<Game::IScene> &scene);

        void pop(const std::string &name);

        void pop();        
                
        void clear();
        
        void remove();

        // getters
        std::size_t size() const;

        std::string name() const;

        bool empty() const;
        
    private:
        /*! the stack of scenes */
        std::stack<std::shared_ptr<Game::IScene>> _scenes;
   };
}