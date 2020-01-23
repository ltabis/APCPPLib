//
// Created by tabis on 22/01/2020.
//

#include <gtest/gtest.h>

#include "SceneStateMachine.hpp"
#include "Logger.hpp"
#include "AScene.hpp"

class SampleScene : public Game::AScene
{
public:
	SampleScene(const std::string &name, std::shared_ptr<Game::IMediator> mediator) : AScene(name, mediator) {}

	void update(float deltaTime) override
		{
			(void) deltaTime;
			Debug::Logger::printDebug(Debug::INFO, "The SampleScene is being updated.", "SampleScene::update()");
		}


	void setVisible(bool visible) override
		{
			Debug::Logger::printDebug(Debug::INFO, "Making all object invisible.", "SampleScene::setVisible()");
		}

	void remove() override
		{
			Debug::Logger::printDebug(Debug::INFO, "Removing all objects.", "SampleScene::remove()");
		}

	void onCreate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onCreate method called.", "SampleScene::onCreate()");
		}

	void onDestroy() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDestroy method called.", "SampleScene::onDestroy()");
		}

	void onActivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onActivate method called.", "SampleScene::onActivate()");
		}

	void onDeactivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDeactivate method called.", "SampleScene::onDeactivate()");
		}
};

TEST(SceneStateMachineTests, SceneStateMachine_basic_methods)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
	std::shared_ptr<Game::SceneStateMachine> machine = std::make_shared<Game::SceneStateMachine>(Game::SceneStateMachine());
	std::shared_ptr<Game::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Game::IScene> scene(new SampleScene("SampleScene", ptr));

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding a scene to the machine.
	machine->push(scene);

    // The manager has one scene in memory, updating it.
    ASSERT_EQ(machine->size(), 1);
	ASSERT_EQ(machine->update(), true);

    // Changing the scene's name.
	machine->setName("Scene name changed!");
	ASSERT_EQ(machine->name(), "Scene name changed!");

    // Clearing the machine.
	machine->clear();

    // Has the machine been cleared ?
    ASSERT_EQ(machine->size(), 0);
}

TEST(SceneStateMachineTests, SceneStateMachine_scene_manipulation)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
	std::shared_ptr<Game::SceneStateMachine> machine = std::make_shared<Game::SceneStateMachine>(Game::SceneStateMachine());
	std::shared_ptr<Game::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Game::IScene> scene1(new SampleScene("SampleScene1", ptr));
	std::shared_ptr<Game::IScene> scene2(new SampleScene("SampleScene2", ptr));

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding scenes to the machine.
	machine->push(scene1);
	machine->push(scene2);

    // The manager has two scenes in memory, updating the first one.
    ASSERT_EQ(machine->size(), 2);
	ASSERT_EQ(machine->update(), true);

	// Checking the name of the scene on the top of the stack.
    ASSERT_EQ(machine->name(), "SampleScene2");

	// Poping the second scene.
	machine->pop();
    ASSERT_EQ(machine->name(), "SampleScene1");
    ASSERT_EQ(machine->size(), 1);

    // Clearing the machine.
	machine->clear();

    // Has the machine been cleared ?
    ASSERT_EQ(machine->size(), 0);
}

TEST(SceneStateMachineTests, SceneStateMachine_advanced_scene_manipulation)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
	std::shared_ptr<Game::SceneStateMachine> machine = std::make_shared<Game::SceneStateMachine>(Game::SceneStateMachine());
	std::shared_ptr<Game::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Game::IScene> scene1(new SampleScene("SampleScene1", ptr));
	std::shared_ptr<Game::IScene> scene2(new SampleScene("SampleScene2", ptr));

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding scenes to the machine.
	machine->push(scene1);

    // The manager has one scene in memory, updating it.
    ASSERT_EQ(machine->size(), 1);
	ASSERT_EQ(machine->update(), true);

	// Checking the name of the scene on the top of the stack.
    ASSERT_EQ(machine->name(), "SampleScene1");

	// Swaping.
	machine->swap(scene2);
    ASSERT_EQ(machine->name(), "SampleScene2");
    ASSERT_EQ(machine->size(), 1);

	// Removing elements from the current scene.
	machine->remove();

	// Push the first one again.
	machine->push(scene1);

	// Poping via string.
	machine->pop("unknown");

	// There isn't any scenes that are called "unknown" so everything as been poped.
    ASSERT_EQ(machine->size(), 0);
}

class Notify : public Game::AScene
{
public:
	Notify(const std::string &name, std::shared_ptr<Game::IMediator> mediator) : AScene(name, mediator) {}

	void update(float deltaTime) override
		{
			(void) deltaTime;

			Debug::Logger::printDebug(Debug::INFO, "The Notify is being updated, poping the scene.", "Notify::update()");

			// calling the mediator for the sake of the example.
			_mediator->notify(Game::POP, nullptr);
		}


	void setVisible(bool visible) override
		{
			Debug::Logger::printDebug(Debug::INFO, "Making all object invisible.", "Notify::setVisible()");
		}

	void remove() override
		{
			Debug::Logger::printDebug(Debug::INFO, "Removing all objects.", "Notify::remove()");

			// Swaping, for the sake of the example.
			_mediator->notify(Game::SWAP, nullptr);
			_mediator->notify(Game::SWAP, new SampleScene("SampleScene", _mediator));
		}

	void onCreate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onCreate method called.", "Notify::onCreate()");
		}

	void onDestroy() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDestroy method called.", "Notify::onDestroy()");
		}

	void onActivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onActivate method called.", "Notify::onActivate()");
		}

	void onDeactivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDeactivate method called.", "Notify::onDeactivate()");
		}
};


TEST(SceneStateMachineTests, SceneStateMachine_notify)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
	std::shared_ptr<Game::SceneStateMachine> machine = std::make_shared<Game::SceneStateMachine>(Game::SceneStateMachine());
	std::shared_ptr<Game::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Game::IScene> scene(new Notify("Notify", ptr));

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding a scene to the machine.
	machine->push(scene);

    // The manager has one scene in memory, updating it.
    ASSERT_EQ(machine->size(), 1);
	ASSERT_EQ(machine->update(), true);

	// The scene should have notified the mediator to pop it.
    ASSERT_EQ(machine->size(), 0);

    // Re-adding a scene to the machine.
	machine->push(scene);
    ASSERT_EQ(machine->size(), 1);

	// Calling the remove method of the Notify class, where we asked it to swap.
	machine->remove();

	// The scene as been swaped with the SampleScene object.
    ASSERT_EQ(machine->size(), 1);
    ASSERT_EQ(machine->name(), "SampleScene");
}