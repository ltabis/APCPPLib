
#include "AScene.hpp"

Game::AScene::AScene(const std::string &name, std::shared_ptr<Game::IMediator> &mediator) : _name(name), _mediator(mediator) {}

void Game::AScene::setName(const std::string &name)
{
    _name = name;
}

std::string Game::AScene::name() const
{
    return _name;
}