#include <chrono>
#include "Logger.hpp"

int main()
{
    using namespace std::chrono_literals;

    Debug::Logger *log = Debug::Logger::getInstance(Debug::STANDARD);
    std::string a = "A default debug message.";

    log->generateDebugMessage(Debug::ERROR, "Error", "main");
    log->generateDebugMessage(Debug::INFO, "Info message", "main");
    log->generateDebugMessage(Debug::WARNING, "Warning message, attention !", "main");
    log->generateDebugMessage(Debug::FATAL, "Fatal message, everything is going haywire !", "main");
    std::this_thread::sleep_for(2s);
    return 0;
}
