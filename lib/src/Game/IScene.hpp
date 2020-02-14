/**
 *  @file     lib/src/Game/IScene.hpp
 *  @author   tabis on the 2020-02-14
 *  @date     2020-02-14
 * 
 *  project: APCPPLib
 * 
 */

#pragma once

#include <stack>
#include <queue>
#include <string>
#include <cstring>

/// @namespace Scenes
/// @brief Used for all scenes components
namespace Game
{

    /// @class IScene
    /// @brief Scene interface
    class IScene
    {
        public:

            /** 
             * @brief Called just after the scene is created.
             */
            virtual void onCreate() = 0;

            /** 
             * @brief Called just before the destructor is called.
             */
            virtual void onDestroy() = 0;

            /** 
             * @brief Used to activate elements of the scene when switching to it.
             */
            virtual void onActivate() = 0;

            /** 
             * @brief Used to set inavtive elements of the scene when we push an other scene to the stack.
             */
            virtual void onDeactivate() = 0;

            /** 
             * @brief Update the scene.
             * @param deltaTime : time computed since the last frame.
             */
            virtual void onUpdate(float deltaTime) = 0;

            /** 
             * @brief Set the name of the scene.
             * @param name : the new name of the scene. 
             */
            virtual void setName(const std::string &name) = 0;

            /** 
             * @brief get the name of the scene.
             * @return the name of the scene.
             */
            virtual std::string name() const = 0;
    };
}