//
// Created by tabis on 09/10/2019.
//

#include "SceneStateMachine.hpp"

Game::SceneStateMachine::~SceneStateMachine()
{
    clear();
}

void Game::SceneStateMachine::notify(const std::string &sender, std::size_t state)
{
    (void) sender;
    (void) state;
    // (void) IScene *newScene;
}

bool Game::SceneStateMachine::update()
{
    if (!empty())
    {
        _scenes.top()->update();
        return true;
    }
    return false;
}

void Game::SceneStateMachine::push(std::shared_ptr<Game::IScene> &scene)
{
    _scenes.push(scene);
}

void Game::SceneStateMachine::swap(std::shared_ptr<Game::IScene> &scene)
{
    if (!empty())
        pop();
    _scenes.push(scene);
}

void Game::SceneStateMachine::pop(const std::string &name)
{
    while (!empty() && _scenes.top()->name() != name)
        _scenes.pop();
}

void Game::SceneStateMachine::pop()
{
    if (!empty())
        _scenes.pop();
}

void Game::SceneStateMachine::clear()
{
    while (!empty())
        pop();
}

void Game::SceneStateMachine::remove()
{
    if (!empty())
        _scenes.top()->remove();
}

std::size_t Game::SceneStateMachine::size() const
{
    return _scenes.size();
}

std::string Game::SceneStateMachine::name() const
{
    return !empty() ? _scenes.top()->name() : "";
}

bool Game::SceneStateMachine::empty() const
{
    return _scenes.empty();
}