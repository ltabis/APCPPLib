//
// Created by tabis on 09/10/2019.
//

#include "SceneStateMachine.hpp"

void Game::SceneStateMachine::push(std::shared_ptr<Game::IScene> &&scene)
{
    _scenes.push(scene);
}

void Game::SceneStateMachine::pop()
{
    _scenes.pop();
}

void Game::SceneStateMachine::pop(const std::string &name)
{
    while (_scenes.top()->name() != name)
        _scenes.pop();
}

void Game::SceneStateMachine::swap(std::shared_ptr<Game::IScene> &&scene)
{
    pop();
    _scenes.push(scene);
}

std::size_t Game::SceneStateMachine::size() const
{
    return _scenes.size();
}

bool Game::SceneStateMachine::empty() const
{
    return _scenes.empty();
}

std::string Game::SceneStateMachine::name() const
{
    return _scenes.top()->name();
}

bool Game::SceneStateMachine::update()
{
    _scenes.top()->update();
    return true;
}

void Game::SceneStateMachine::clear()
{
    while (!empty())
        pop();
}

void Game::SceneStateMachine::remove()
{
    _scenes.top()->remove();
}