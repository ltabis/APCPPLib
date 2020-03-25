
#include "AScene.hpp"

void Scenes::AScene::onInit(const std::string &name, Module::IMediator *mediator)
{
    _name = name;
    _mediator = mediator;
}

void Scenes::AScene::setName(const std::string &name)
{
    _name = name;
}

std::string Scenes::AScene::name() const
{
    return _name;
}