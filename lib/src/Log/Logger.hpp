/*
*
*   Lucas Tabis
*   Logger class source file
*
*
*/

#include <string>
#include <iostream>
#include <fstream>
#include "macro.hpp"

#define DEFAULT_LOG_FILE    "output.txt"
#define INFO_MESSAGE        "[Info]"
#define WARNING_MESSAGE     "[Warning]"
#define ERROR_MESSAGE       "[Error]"

namespace Debug {

    typedef enum e_mode {STANDARD, FILE, OFF} mode;
    typedef enum e_type {INFO, WARNING, ERROR} type;

    class Logger {
        public:
            Logger(mode mode = STANDARD);
            ~Logger();

            void switchMode(mode mode, const std::string &filePath = std::string());
            void generateDebugMessage(type type, const std::string &message, const std::string &where);

        private:
            void generateMessageInFile(type type, const std::string &message, const std::string &where);
            void generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where);
            std::string getMessageFromType(type type) {return type == INFO ? INFO_MESSAGE : type == WARNING ? WARNING_MESSAGE : ERROR_MESSAGE;};
            std::string getMessageColorFromType(type type) {return type == INFO ? GREEN : type == WARNING ? YELLOW : RED;};

            mode _mode;
            std::ofstream _file;
    };
}