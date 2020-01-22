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

	void update() override
		{
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
};

TEST(SceneStateMachineTests, SceneMachineBasicMethods)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
	std::shared_ptr<Game::SceneStateMachine> machine = std::make_shared<Game::SceneStateMachine>(Game::SceneStateMachine());
	std::shared_ptr<Game::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a machine stoped running.
	std::shared_ptr<Game::IScene> scene(new SampleScene("SampleScene", ptr));

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding a scene to the machine.
	machine->push(scene);

    // The manager has one scene in memory, updating it.
    ASSERT_EQ(machine->size(), 1);
	ASSERT_EQ(machine->update(), false);

    // Clearing the machine.
	machine->clear();

    // Has the machine been cleared ?
    ASSERT_EQ(machine->size(), 0);
}
