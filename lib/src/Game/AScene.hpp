/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene class interface
*/

#pragma once

#include "IScene.hpp"
#include "SceneStateMachine.hpp"

namespace Game
{

    /// \class AScene
    /// \brief AScene interface
    class AScene : public IScene
    {

        public:
            AScene(const std::string &name, std::shared_ptr<Game::IMediator> &mediator);

            /// \param name : the new name of the current scene
            /// \brief change the name of the scene
            void setName(const std::string &name) override;

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            std::string name() const override;

        protected:

            std::string _name;

            std::shared_ptr<Game::IMediator> _mediator;
    };
}