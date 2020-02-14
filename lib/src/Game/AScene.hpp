/**
 *  @file     lib/src/Game/AScene.hpp
 *  @author   tabis on the 2020-02-14
 *  @date     2020-02-14
 * 
 *  project: APCPPLib
 * 
 */

#pragma once

#include "IScene.hpp"
#include "SceneStateMachine.hpp"

/// @namespace Game.
/// @brief game namespace.
namespace Game
{

    /// @enum AScene
    /// @brief An abstract class used to implement redundant methods of the IScene interface.
    class AScene : public IScene
    {

        public:
            /** 
             * @brief Constructor.
             * @param name : the name of the scene.
             * @param mediator : the mediator instance needed to call the `notify` method.
             */
            AScene(const std::string &name, std::shared_ptr<Game::IMediator> &mediator);

            /** 
             * @brief Set the name of the scene.
             * @param name : the new name of the scene.
             */
            void setName(const std::string &name) override;

            /** 
             * @brief Get the name of the scene.
             * @return the name of the scene.
             */
            std::string name() const override;

        protected:

            /*! The name of the scene */
            std::string _name;

            /*! The mediator interface instance */
            std::shared_ptr<Game::IMediator> _mediator;
    };
}