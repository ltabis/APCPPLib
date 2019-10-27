#include <vector>
#include "Logger.hpp"

int main()
{
    Debug::Logger *log = Debug::Logger::getInstance();

    log->generateDebugMessage(Debug::ERROR, "Error", "main");
    return 0;
}
