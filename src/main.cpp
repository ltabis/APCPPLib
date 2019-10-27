#include <chrono>
#include "Logger.hpp"

int main()
{
    using namespace std::chrono_literals;

    Debug::Logger *log = Debug::Logger::getInstance();

    log->switchMode(Debug::FILE);
    log->generateDebugMessage(Debug::ERROR, "Error", "main");
    log->generateDebugMessage(Debug::INFO, "Info message", "main");
    std::this_thread::sleep_for(2s);
    return 0;
}
