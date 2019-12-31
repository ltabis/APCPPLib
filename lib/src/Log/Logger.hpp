/*
*
*   Lucas Tabis
*   Logger class source file
*
*
*/

#pragma once

#include <ratio>
#include <queue>
#include <mutex>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <condition_variable>

#include "macro.hpp"

namespace Debug
{

    typedef enum e_mode {STANDARD, FILE, OFF} mode;
    typedef enum e_type {DEBUG = 2, INFO = 4, WARNING = 8, ERROR = 16, FATAL = 32} type;

    class Logger
    {
        public:
            // Illegal methods
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            // Dtor.
            ~Logger();
        
            // Singleton instance
            static Logger *getInstance(mode mode = STANDARD, char flags = Flags::all_on)
            {
                static std::unique_ptr<Logger> loggerObject(new Logger(flags, mode));

                return loggerObject.get();
            }

            static void generateDebugMessageStatic(type type, const std::string &message, const std::string &where = "unknown")
            {
                Logger *instance = getInstance();

                instance->generateDebugMessage(type, message, where);
            }

            void setFlags(char flags);
            void switchMode(mode mode);
            void generateDebugMessage(type type, const std::string &message, const std::string &where = "unknown");
            void generateDebugMessage(const std::string &formated);
            void setFileOutput(const std::string &filepath);

        private:
            Logger(const std::string &filepath, char flags = Flags::all_on, mode mode = FILE);
            Logger(char flags = Flags::all_on, mode mode = STANDARD);

            void writeContent();
            std::string getCurrentTimeString();
            void generateMessageInFile(type type, const std::string &message, const std::string &where);
            void generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where);
            std::string getMessageFromType(type type) {return type == INFO ? INFO_MESSAGE :
                                                              type == WARNING ? WARNING_MESSAGE :
                                                              type == ERROR ? ERROR_MESSAGE :
                                                              type == FATAL ? FATAL_MESSAGE : DEBUG_MESSAGE;};
            std::string getMessageColorFromType(type type) {return type == INFO ? GREEN :
                                                                   type == WARNING ? YELLOW :
                                                                   type == ERROR ? RED :
                                                                   type == FATAL ? REDUNDERLINED : "";};

            mode _mode;
            char _flags;
            std::ofstream _file;
            std::queue<std::string> _queue;

            std::thread _worker;
            std::mutex _notifiedMutex;

            std::condition_variable _condVar;
            bool _bNotified;
            bool _bIsWorkerActive;
            std::chrono::high_resolution_clock::time_point _time;
    };
}
