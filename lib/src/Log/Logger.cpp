/*
 *
 *   Lucas Tabis
 *   Logger class source file
 *
 *
 */

#include "Logger.hpp"

Debug::Logger *Debug::Logger::_singleton = nullptr;

/*
 *   Construcor / Destructor.
 */

Debug::Logger::Logger(mode mode) : _mode(mode), _file(DEFAULT_LOG_FILE), _worker(std::thread(&Logger::writeContent, this)) {}
Debug::Logger::Logger(const std::string &filePath, mode mode) : _mode(mode), _file(filePath), _worker(std::thread(&Logger::writeContent, this)) {}

Debug::Logger::~Logger() {}

void Debug::Logger::switchMode(mode mode, const std::string &filePath)
{
    while (!_queue.empty())
        _queue.pop();
    if (_mode == mode)
        return;
    _mode = mode;
    if (mode == FILE)
        _file.open(filePath.empty() ? DEFAULT_LOG_FILE : filePath, std::ios::app);
    else
        if (_file.is_open())
            _file.close();
}

void Debug::Logger::writeContent()
{
    if (!_queue.empty()) {
        std::mutex mutex;
        mutex.lock();
        if (_mode) {
            generateDebugMessage(_queue.back());
            _queue.pop();
        }
        mutex.unlock();
    }
}

void Debug::Logger::stopThread()
{
    _worker.join();
}

void Debug::Logger::addContentToQueue(std::string message)
{
    _queue.push(message);
}

//// USER ACCESS

/*
 *   generate a debug message with a type and where parameters.
 */

void Debug::Logger::generateDebugMessage(type type, const std::string &message, const std::string &where)
{
    if (_mode == OFF)
        return;
    else if (_mode == STANDARD)
        generateMessageOnStandardOutput(type, message, where);
    else if (_mode == FILE)
        generateMessageInFile(type, message, where);
}

void Debug::Logger::generateDebugMessage(const std::string &formated)
{
    if (_mode == OFF)
        return;
    else if (_mode == STANDARD)
        std::cout << formated;
    else if (_mode == FILE)
        _file << formated;
}


void Debug::Logger::generateMessageInFile(type type, const std::string &message, const std::string &where)
{
    addContentToQueue(getMessageFromType(type) + " " + message +  " in " + where);
}

void Debug::Logger::generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where)
{
    addContentToQueue(getMessageColorFromType(type) + getMessageFromType(type) + " " + CYAN + message + WHITE + " in " + MAGENTA + where + WHITE);
}