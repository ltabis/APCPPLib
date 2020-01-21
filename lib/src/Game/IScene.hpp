/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene class interface
*/

#pragma once

#include <stack>
#include <queue>
#include <string>
#include <cstring>

/// \namespace Scenes
/// \brief Used for all scenes components
namespace Game
{

    /// \class IScene
    /// \brief Scene interface
    class IScene
    {
        public:

            /// \return a scene representing the state of the scene
            /// \brief run the scenes logic
            virtual void onCreate() = 0;

            /// \return a scene representing the state of the scene
            /// \brief run the scenes logic
            virtual void update() = 0;

            /// \param name : the new name of the current scene
            /// \brief change the name of the scene
            virtual void setName(const std::string &name) = 0;

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            virtual std::string name() const = 0;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            virtual void setVisible(bool b) = 0;
            
            /// \brief remove all the entities of the scene
            virtual void remove() = 0;
    };
}