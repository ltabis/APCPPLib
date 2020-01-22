//
// Created by tabis on 09/10/2019.
//

#include "SceneStateMachine.hpp"

Game::SceneStateMachine::SceneStateMachine()
{
    _callbacks.emplace(POP, &SceneStateMachine::popCallback);
    _callbacks.emplace(SWAP, &SceneStateMachine::swapCallback);
}

Game::SceneStateMachine::~SceneStateMachine()
{
    clear();
}

void Game::SceneStateMachine::notify(const std::string &sender, Game::scene_state state, Game::IScene *new_scene)
{
    // That should not happen.
    if (sender != _scenes.top()->name())
        return;

    _callbacks[state](*this, new_scene);
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