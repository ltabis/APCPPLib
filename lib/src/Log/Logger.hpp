/*
*
*   Lucas Tabis
*   Logger class source file
*
*
*/

#pragma once

#include <queue>
#include <mutex>
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <condition_variable>

#include "macro.hpp"

#define DEFAULT_LOG_FILE    "output.txt"
#define WARNING_MESSAGE     "[Warning]"
#define ERROR_MESSAGE       "[Error]"
#define DEBUG_MESSAGE       "[Debug]"
#define INFO_MESSAGE        "[Info]"

namespace Debug {

    typedef enum e_mode {STANDARD, FILE, OFF} mode;
    typedef enum e_type {INFO, WARNING, ERROR} type;

    class Logger {
        public:
            // Illegal methods
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            // Singleton instance.
            static Logger *getInstance(const std::string &filePath)
            {
                if (!_singleton)
                    _singleton = new Logger(filePath, FILE);
                return _singleton;
            }
            static Logger *getInstance()
            {
                if (!_singleton)
                    _singleton = new Logger(STANDARD);
                return _singleton;
            }
            static void stopInstance()
            {
                if (!_singleton)
                    return;
                _singleton->stopThread();
            }

            void switchMode(mode mode, const std::string &filePath = std::string());
            void generateDebugMessage(type type, const std::string &message, const std::string &where);
            void generateDebugMessage(const std::string &formated);

            void operator<<(const std::string &message);

        private:
            Logger(const std::string &filepath, mode mode = FILE);
            Logger(mode mode = STANDARD);
            ~Logger();

            void writeContent();
            void stopThread();
            void addContentToQueue(std::string message);
            void generateMessageInFile(type type, const std::string &message, const std::string &where);
            void generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where);
            std::string getMessageFromType(type type) {return type == INFO ? INFO_MESSAGE : type == WARNING ? WARNING_MESSAGE : ERROR_MESSAGE;};
            std::string getMessageColorFromType(type type) {return type == INFO ? GREEN : type == WARNING ? YELLOW : RED;};

            static Logger *_singleton;

            mode _mode;
            std::ofstream _file;
            std::queue<std::string> _queue;

            std::thread _worker;
            std::mutex _queueMutex;
            std::mutex _coutMutex;
            std::mutex _notifiedMutex;

            std::condition_variable _condVar;
            bool _notified;
    };
}