/*
 *
 *   Lucas Tabis
 *   Logger class source file
 *
 *
 */

#include "Logger.hpp"

Debug::Logger::Logger(char flags, mode mode)
    : _mode            { mode                                      }
    , _flags           { flags                                     }
    , _bNotified       { false                                     }
    , _bIsWorkerActive { true                                      }
    , _time            { std::chrono::high_resolution_clock::now() }
{
    // Creating a new worker thread that will print content.
    _worker = std::thread(&Logger::writeContent, this);
}

Debug::Logger::Logger(const std::string &filePath, char flags, mode mode)
    : _mode            { mode                                      }
    , _flags           { flags                                     }
    , _file            { filePath                                  }
    , _bNotified       { false                                     }
    , _bIsWorkerActive { true                                      }
    , _time            { std::chrono::high_resolution_clock::now() }
{
    // Creating a new worker thread that will print content.
    _worker = std::thread(&Logger::writeContent, this);
}

Debug::Logger::~Logger()
{
    _bNotified = true;
    _bIsWorkerActive = false;
    _condVar.notify_one();
    _worker.join();
    if (_file.is_open())
        _file.close();
}

void Debug::Logger::writeContent()
{
    std::unique_lock<std::mutex> lock(_notifiedMutex);

    while (_bIsWorkerActive)
    {
        // Waiting for the thread to be unlocked.
        while (!_bNotified)
            _condVar.wait(lock);

        // Writing all messages to the disered output.
        while (!_queue.empty() && _mode != OFF)
        {
            printDebug(_queue.front());
            _queue.pop();
        }
        _bNotified = false;
    }
}

void Debug::Logger::generateMessageInFile(type type, const std::string &message, const std::string &where)
{
    _queue.push(getCurrentTimeString() +
                getMessageFromType(type) + " " + message +  " in " + where);
}

void Debug::Logger::generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where)
{
    _queue.push(getCurrentTimeString() +
                getMessageColorFromType(type) +
                getMessageFromType(type) + CYAN + " " + message + WHITE + " in " + MAGENTA + where + WHITE);
}

std::string Debug::Logger::getCurrentTimeString()
{
    std::ostringstream oss;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    // Weird conversions to get the time of the log (to be optimised).
    oss << (_mode == FILE ? std::put_time(&tm, "(%d-%m-%Y %Hh %Mm %Ss") : std::put_time(&tm, "(%Hh %Mm %Ss"));
    oss << " " << std::to_string((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()) % 1000).count()) << "ms";
    return _mode == FILE ? oss.str() + ") " : BLUE + oss.str() + ") " + WHITE;
}
