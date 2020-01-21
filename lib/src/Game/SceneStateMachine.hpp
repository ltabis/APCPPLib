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

        void notify(const std::string &sender, std::size_t state);
    };

    class SceneStateMachine : public IMediator
    {
    public:
        
        inline void push(std::shared_ptr<Game::IScene> &&scene);
        
        /// \brief Destroy the scene on top of the stack
        inline void pop();
        
        /// \param name : Last scene to destroy
        /// \brief Destroy all scenes unit the current scene corespond to the name parameter
        inline void pop(const std::string &name);
        
        /// \param scene : The scene to replace
        /// \brief Swap the current scene with the scene passed as parameter
        inline void swap(std::shared_ptr<Game::IScene> &&scene);
        
        /// \return the size of the stack
        /// \brief get the size of the stack
        inline std::size_t size() const;

        inline bool empty() const;

        /// \return the name of the current scene
        /// \brief get the name of the current scene
        inline std::string name() const;
        
        inline bool update();
        
        /// \brief clear all scenes in the stack
        inline void clear();
        
        /// \brief remove elements of top scene
        inline void remove();

        private:
            /*! the stack of scenes */
            std::stack<std::shared_ptr<Game::IScene>> _scenes;
   };
}