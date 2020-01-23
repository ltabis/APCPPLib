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

            virtual void onCreate() = 0;

            virtual void onDestroy() = 0;

            virtual void onActivate() = 0;

            virtual void onDeactivate() = 0;

            virtual void update(float deltaTime) = 0;

            virtual void setName(const std::string &name) = 0;

            virtual std::string name() const = 0;
    };
}