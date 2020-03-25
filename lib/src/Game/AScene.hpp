
#pragma once

#include "IScene.hpp"

namespace Scenes
{

    class AScene : public IScene
    {

        public:

            AScene() = default;

            ~AScene() override = default;

            void onInit(const std::string &name, Module::IMediator *mediator) override;

            void setName(const std::string &name) override;

            std::string name() const override;

        protected:

            std::string _name;

            Module::IMediator *_mediator;
    };
}