#include <vector>
#include "Logger.hpp"

int main()
{
    Debug::Logger *log = Debug::Logger::getInstance();

    log->generateDebugMessage(Debug::ERROR, "Error", "main");
    log->generateDebugMessage(Debug::INFO, "Info message", "main");
    Debug::Logger::stopInstance();
    return 0;
}
