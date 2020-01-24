//
// Created by tabis on 09/10/2019.
//

#include "SceneStateMachine.hpp"

Game::SceneStateMachine::SceneStateMachine() : _deltaTime(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
    _callbacks.emplace(POP, std::bind(&SceneStateMachine::popCallback, this, std::placeholders::_1, std::placeholders::_2));
    _callbacks.emplace(SWAP, std::bind(&SceneStateMachine::swapCallback, this, std::placeholders::_1, std::placeholders::_2));
    _callbacks.emplace(PUSH, std::bind(&SceneStateMachine::pushCallback, this, std::placeholders::_1, std::placeholders::_2));
}

Game::SceneStateMachine::~SceneStateMachine()
{
    clear();
}

void Game::SceneStateMachine::notify(Game::IScene *sender, Game::scene_state state, Game::IScene *new_scene)
{
    _callbacks[state](sender, new_scene);
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
    // Deactivating the last scene before pushing a new one.
    if (!empty())
        _scenes.top()->onDeactivate();

    // Pushing the new scene and call the onCreate() method.
    _scenes.push(scene);
    _scenes.top()->onCreate();
}

void Game::SceneStateMachine::swap(std::shared_ptr<Game::IScene> &scene)
{
    // poping the current scene if the stack isn't empty.
    if (!empty())
        pop();

    // Pushing the new scene and call the onCreate() method.
    // We can't use the push() method because it could modify the scene before the one to be swaped.
    _scenes.push(scene);
    _scenes.top()->onCreate();
}

void Game::SceneStateMachine::pop(const std::string &name)
{
    // Poping the scenes until the name is reached.
    while (!empty() && _scenes.top()->name() != name)
    {
        _scenes.top()->onDestroy();
        _scenes.pop();
    }

    // Activating the last scene if the stack isn't empty.
    if (!empty())
        _scenes.top()->onActivate();
}

void Game::SceneStateMachine::pop()
{
    if (!empty())
    {
        // Destroying the scene and poping it.
        _scenes.top()->onDestroy();
        _scenes.pop();

        // If there is still a scene on the stack, activating it.
        if (!empty())
            _scenes.top()->onActivate();
    }
}

void Game::SceneStateMachine::clear()
{
    // Poping all scenes unitil there is nothing left.
    while (!empty())
        pop();
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

void Game::SceneStateMachine::popCallback(IScene *sender, IScene *scene)
{
    (void) scene;
    (void) sender;

    pop();
}

void Game::SceneStateMachine::swapCallback(IScene *sender, IScene *scene)
{
    if (!scene)
        return;

    // Transforming pointer into a shared one.
    std::shared_ptr<IScene> ptr(scene);
    swap(ptr);
}

void Game::SceneStateMachine::pushCallback(IScene *sender, IScene *scene)
{
    if (!sender || !scene)
        return;

    // Transforming pointer into a shared one.
    std::shared_ptr<IScene> ptr(scene);
    push(ptr);
}