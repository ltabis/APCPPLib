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

Debug::Logger::Logger(mode mode) : _mode(mode), _file(DEFAULT_LOG_FILE), _notified(false), _isWorkerActive(true)
{
    _worker = std::thread(&Logger::writeContent, this);
}
Debug::Logger::Logger(const std::string &filePath, mode mode) : _mode(mode), _file(filePath), _notified(false), _isWorkerActive(true)
{
    _worker = std::thread(&Logger::writeContent, this);
}

Debug::Logger::~Logger()
{
    std::cout << "Logger as been destroyed" << std::endl;
}

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
    std::unique_lock<std::mutex> lock(_notifiedMutex);

    while (_isWorkerActive) {
        while (!_notified)
            _condVar.wait(lock);
        if (_mode == OFF)
            continue;
        while (!_queue.empty()) {
            generateDebugMessage(_queue.back());
            _queue.pop();
        }
    _notified = false;
    }
}

void Debug::Logger::stopThread()
{
    _condVar.notify_one();
    _isWorkerActive = false;
    _worker.join();
    delete _singleton;
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

void Debug::Logger::generateDebugMessage(const std::string &formated)
{
    if (_mode == STANDARD)
        std::cout << formated;
    else if (_mode == FILE)
        _file << formated;
}

void Debug::Logger::generateMessageInFile(type type, const std::string &message, const std::string &where)
{
    _queue.push(getMessageFromType(type) + " " + message +  " in " + where);
}

void Debug::Logger::generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where)
{
    _queue.push(getMessageColorFromType(type) + getMessageFromType(type) + " " + CYAN + message + WHITE + " in " + MAGENTA + where + WHITE + "\n");
}