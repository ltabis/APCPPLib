
#include "AScene.hpp"

void Game::AScene::setName(const std::string &name)
{
    _name = name;
}

std::string Game::AScene::name() const
{
    return _name;
}