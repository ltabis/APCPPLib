
#pragma once

#include "IScene.hpp"
#include "SceneStateMachine.hpp"

namespace Game
{

    class AScene : public IScene
    {

        public:
            AScene(const std::string &name, std::shared_ptr<Game::IMediator> &mediator);

            void setName(const std::string &name) override;

            std::string name() const override;

        protected:

            std::string _name;

            std::shared_ptr<Game::IMediator> _mediator;
    };
}