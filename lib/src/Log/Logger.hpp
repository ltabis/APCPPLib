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
#include <memory>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <condition_variable>

#include "macro.hpp"

#define DEFAULT_LOG_FILE    "output.txt"
#define WARNING_MESSAGE     "[Warning]"
#define ERROR_MESSAGE       "[Error]"
#define DEBUG_MESSAGE       "[Debug]"
#define INFO_MESSAGE        "[Info]"

namespace Debug {

    // Flags options for the Logger class
    namespace Flags {
        #define F_INFO    0
        #define F_ERROR   1
        #define F_DEBUG   2
        #define F_WARNING 3
    }

    typedef enum e_mode {STANDARD, FILE, OFF} mode;
    typedef enum e_type {INFO, WARNING, ERROR, FATAL, MUNDANE} type;

    class Logger {
        public:
            // Illegal methods
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            // Singleton instance and dtor.
            ~Logger();
            static Logger *getInstance(const std::string &filePath = DEFAULT_LOG_FILE)
            {
                static std::unique_ptr<Logger> loggerObject(new Logger(filePath, STANDARD));

                return loggerObject.get();
            }

            void setFlags(const std::string &flags);
            void switchMode(mode mode, const std::string &filePath = std::string());
            void generateDebugMessage(type type, const std::string &message, const std::string &where);
            void generateDebugMessage(const std::string &formated);

        private:
            Logger(const std::string &filepath, mode mode = FILE);
            Logger(mode mode = STANDARD);

            void writeContent();
            std::string getCurrentTimeString();
            void generateMessageInFile(type type, const std::string &message, const std::string &where);
            void generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where);
            std::string getMessageFromType(type type) {return type == INFO ? INFO_MESSAGE : type == WARNING ? WARNING_MESSAGE : ERROR_MESSAGE;};
            std::string getMessageColorFromType(type type) {return type == INFO ? GREEN : type == WARNING ? YELLOW : RED;};

            mode _mode;
            std::ofstream _file;
            std::queue<std::string> _queue;

            std::thread _worker;
            std::mutex _notifiedMutex;

            std::condition_variable _condVar;
            bool _notified;
            bool _isWorkerActive;
            std::chrono::high_resolution_clock::time_point _time;
    };
}