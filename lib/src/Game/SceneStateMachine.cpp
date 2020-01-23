//
// Created by tabis on 09/10/2019.
//

#include "SceneStateMachine.hpp"

Game::SceneStateMachine::SceneStateMachine() : _deltaTime(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
    _callbacks.emplace(POP, &SceneStateMachine::popCallback);
    _callbacks.emplace(SWAP, &SceneStateMachine::swapCallback);
}

Game::SceneStateMachine::~SceneStateMachine()
{
    clear();
}

void Game::SceneStateMachine::notify(Game::scene_state state, Game::IScene *new_scene)
{
    _callbacks[state](*this, new_scene);
}

bool Game::SceneStateMachine::update()
{
    _deltaTime = std::chrono::high_resolution_clock::now().time_since_epoch().count() - _deltaTime;

    if (!empty())
    {
        _scenes.top()->update(_deltaTime);
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

void Game::SceneStateMachine::setName(const std::string &name)
{
    if (!empty())
        _scenes.top()->setName(name);
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

void Game::SceneStateMachine::popCallback(IScene *scene)
{
    (void) scene;

    pop();
}

void Game::SceneStateMachine::swapCallback(IScene *scene)
{
    if (!scene)
        return;

    // Tra,sforming pointer into a shared one.
    std::shared_ptr<IScene> ptr(scene);
    swap(ptr);
}