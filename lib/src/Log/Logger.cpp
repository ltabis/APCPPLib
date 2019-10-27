/*
 *
 *   Lucas Tabis
 *   Logger class source file
 *
 *
 */

#include "Logger.hpp"

/*
 *   Construcor / Destructor.
 */

Debug::Logger::Logger(mode mode) : _mode(mode), _notified(false), _isWorkerActive(true)
{
    _worker = std::thread(&Logger::writeContent, this);
}
Debug::Logger::Logger(const std::string &filePath, mode mode) : _mode(mode), _notified(false), _isWorkerActive(true)
{
    _worker = std::thread(&Logger::writeContent, this);
}

Debug::Logger::~Logger()
{
    if (_file.is_open())
        _file.close();
    _notified = true;
    _isWorkerActive = false;
    _condVar.notify_one();
    _worker.join();
}

void Debug::Logger::switchMode(mode mode, const std::string &filePath)
{
    _mode = mode;
    if (mode == FILE) {
        if (_file.is_open())
            _file.close();
        _file.open(filePath.empty() ? DEFAULT_LOG_FILE : filePath, std::ofstream::out | std::ofstream::app);
    } else
        if (_file.is_open())
            _file.close();
}

void Debug::Logger::writeContent()
{
    std::unique_lock<std::mutex> lock(_notifiedMutex);

    while (_isWorkerActive) {
        while (!_notified)
            _condVar.wait(lock);
        if (_mode == OFF)
            continue;
        while (!_queue.empty()) {
            generateDebugMessage(_queue.front());
            _queue.pop();
        }
    _notified = false;
    }
}

//// USER ACCESS

/*
 *   generate a debug message with a type and where parameters.
 */

void Debug::Logger::generateDebugMessage(type type, const std::string &message, const std::string &where)
{
    if (_mode == STANDARD)
        generateMessageOnStandardOutput(type, message, where);
    else if (_mode == FILE)
        generateMessageInFile(type, message, where);
    _condVar.notify_one();
    _notified = true;
}

#include <exception>

void Debug::Logger::generateDebugMessage(const std::string &formated)
{
    if (_mode == STANDARD)
        std::cout << formated;
    else if (_mode == FILE && _file.is_open())
        _file << formated;
}

void Debug::Logger::generateMessageInFile(type type, const std::string &message, const std::string &where)
{
    _queue.push(getMessageFromType(type) + " " + message +  " in " + where + "\n");
}

void Debug::Logger::generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where)
{
    _queue.push(getMessageColorFromType(type) + getMessageFromType(type) + " " + CYAN + message + WHITE + " in " + MAGENTA + where + WHITE + "\n");
}