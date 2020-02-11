#include "Logger.hpp"
#include "Breakpoint.hpp"
#include "SceneStateMachine.hpp"
#include "AScene.hpp"

#include "BubbleSort.hpp"

class SampleScene : public Game::AScene
{
public:
	SampleScene(const std::string &name, std::shared_ptr<Game::IMediator> mediator) : AScene(name, mediator) {}

	void update(float deltaTime) override
		{
			(void) deltaTime;

			Debug::Logger::printDebug(Debug::INFO, "The SampleScene is being updated.", "SampleScene::update()");
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

// int main()
// {
// 	std::shared_ptr<Game::SceneStateMachine> machine = std::make_shared<Game::SceneStateMachine>(Game::SceneStateMachine());
// 	std::shared_ptr<Game::IMediator> ptr(machine);

// 	std::shared_ptr<Game::IScene> scene(new SampleScene("SampleScene", ptr));

// 	machine->update();

// 	machine->push(scene);

// 	machine->update();

// 	machine->clear();
// 	return 0;
// }

int main()
{
	std::vector<float> vec{0, 1, 2, 4, 3, 1 , 1, 0};

	Algorithm::bubble_sort(vec);

	for (auto &it : vec)
	{
		std::cout << it << ", ";
	}
	std::cout << std::endl;
	std::cout << Algorithm::is_sorted(vec) << std::endl;
	return 0;
}